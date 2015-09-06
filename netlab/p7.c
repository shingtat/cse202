/*
 * p7.c - A sequential HTTP/1.0 web server with dynamically loaded
 *        server-side scripts
 */
#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#include "csapp.h"
#include "support.h"

/*
 * Information about this student team
 */
extern struct team_t team;

/*
 * For managing our function pointers
 */
#define COUNTER_EXT   0
#define TRANSLATE_EXT 1
#define RANDCRAWL_EXT 2
#define ADD_EXT       3
#define NUM_EXTS      4

/*
 * The array of function pointers for the extensions that are loaded
 */
struct managed_extension extensions[NUM_EXTS] = {{NULL}};

/*
 * Forward-declare functions that are defined in this file, so we can start
 * the code listing with main()
 */
void handle_connection(int fd);
void read_requesthdrs(rio_t *rp);
int  parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void usage(char* progname);
void init_extensions();
void fini_extensions();

/*
 * main - The main routine is a very basic server loop
 */
int main(int argc, char **argv) {
  /* for sockets */
  int listenfd, connfd, clientlen;
  struct sockaddr_in clientaddr;

  /* default port... can override with -p */
  int port = 8000;

  /* don't run a full web server... set with -t */
  int simple_test = 0;

  /* for getopt */
  long opt;

  /* run a team name check */
  if (strcmp("", team.name1) == 0) {
    printf("%s: Please fill in the team struct in team.c\n", argv[0]);
    exit(1);
  }
  printf("Member 1: %s\n", team.name1);
  printf("Email 1: %s\n", team.email1);
  if (*team.name2 || *team.email2) {
    printf("Member 2: %s\n", team.name2);
    printf("Email 2: %s\n", team.email2);
  }
  printf("\n");

  /*
   * parse the command-line options.  They are -p <int> for the port, and -h
   * (no parameter) to print help and quit.  -t is for doing very simple
   * tests without starting a web client
   */
  while ((opt = getopt(argc, argv, "p:ht")) != -1) {
    switch(opt) {
     case 'p': port = strtol(optarg, NULL, 10); break;
     case 't': simple_test = 1; break;
     case 'h': usage(argv[0]); break;
     default : usage(argv[0]); break;
    }
  }

  /* load the extensions */
  init_extensions();

  /* should we run the simple test? */
  if (simple_test) {
    extensions[ADD_EXT].func_ptr("v1=7&v2=6", 1);
    fini_extensions();
    exit(0);
  }

  /* listen for connections, serve them */
  listenfd = Open_listenfd(port);
  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    handle_connection(connfd);
    Close(connfd);
  }

  /* close .so libraries */
  fini_extensions();
}

/*
 * handle_connection - handle one HTTP request/response transaction
 */
void handle_connection(int fd) {
  int is_static;
  struct stat sbuf;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char filename[MAXLINE], cgiargs[MAXLINE];
  rio_t rio;

  /* Read request line and headers */
  Rio_readinitb(&rio, fd);
  Rio_readlineb(&rio, buf, MAXLINE);
  sscanf(buf, "%s %s %s", method, uri, version);

  /* make sure it's a GET */
  if (strcasecmp(method, "GET")) {
    clienterror(fd, method, "501", "Not Implemented", "The server does not implement this method");
    return;
  }

  /* Parse URI from GET request */
  read_requesthdrs(&rio);
  is_static = parse_uri(uri, filename, cgiargs);

  /* if the file doesn't exist, stop */
  if (stat(filename, &sbuf) < 0) {
    clienterror(fd, filename, "404", "Not found", "The server couldn't find this file");
    return;
  }

  /* Serve static content */
  if (is_static) {
    if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
      clienterror(fd, filename, "403", "Forbidden", "The server couldn't read the file");
      return;
    }
    serve_static(fd, filename, sbuf.st_size);
  }

  /* Serve dynamic content */
  else {
    if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
      clienterror(fd, filename, "403", "Forbidden", "The server couldn't run the CGI program");
      return;
    }
    serve_dynamic(fd, filename, cgiargs);
  }
}

/*
 * read_requesthdrs - read and parse HTTP request headers
 */
void read_requesthdrs(rio_t *rp) {
  char buf[MAXLINE];

  Rio_readlineb(rp, buf, MAXLINE);
  while (strcmp(buf, "\r\n")) {
    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
  }
  return;
}

/*
 * parse_uri - parse URI into filename and CGI args
 *             return 0 if dynamic content, 1 if static
 */
int parse_uri(char *uri, char *filename, char *cgiargs) {
  char *ptr;

  /* handle static file request */
  if (!strstr(uri, "cgi-bin")) {
    strcpy(cgiargs, "");
    strcpy(filename, ".");
    strcat(filename, uri);
    if (uri[strlen(uri)-1] == '/')
      strcat(filename, "index.html");
    return 1;
  }

  /* handle dynamic file request */
  else {
    ptr = index(uri, '?');
    if (ptr) {
      strcpy(cgiargs, ptr+1);
      *ptr = '\0';
    }
    else {
      strcpy(cgiargs, "");
    }
    strcpy(filename, ".");
    strcat(filename, uri);
    printf("%s\n", filename);
    return 0;
  }
}

/*
 * serve_static - copy a file back to the client
 */
void serve_static(int fd, char *filename, int filesize) {
  int srcfd;
  char *srcp, filetype[MAXLINE], buf[MAXBUF];

  /* Send response headers to client */
  get_filetype(filename, filetype);
  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  sprintf(buf, "%sServer: CSE202 Web Server\r\n", buf);
  sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
  sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
  Rio_writen(fd, buf, strlen(buf));

  /* Send response body to client */
  srcfd = Open(filename, O_RDONLY, 0);
  srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
  Close(srcfd);
  Rio_writen(fd, srcp, filesize);
  Munmap(srcp, filesize);
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) {
  if (strstr(filename, ".html"))
    strcpy(filetype, "text/html");
  else if (strstr(filename, ".gif"))
    strcpy(filetype, "image/gif");
  else if (strstr(filename, ".jpg"))
    strcpy(filetype, "image/jpeg");
  else
    strcpy(filetype, "text/plain");
}

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
void serve_dynamic(int fd, char *filename, char *cgiargs) {
  char buf[MAXLINE], *emptylist[] = { NULL } ;
  int i;

  printf(cgiargs);
  printf("\n");

  /* Return first part of HTTP response */
  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Server: CSE202 Web Server\r\n");
  Rio_writen(fd, buf, strlen(buf));

  /* Find the right extension and run it */
  for (i = 0; i < NUM_EXTS; ++i) {
    if (0 == strcmp(filename, extensions[i].pathname)) {
      extensions[i].func_ptr(cgiargs, fd);
      break;
    }
  }
}

/*
 * clienterror - returns an error message to the client
 */
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) {
  char buf[MAXLINE], body[MAXBUF];

  /* Build the HTTP response body */
  sprintf(body, "<html><title>Server Error</title>");
  sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
  sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
  sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
  sprintf(body, "%s<hr><em>CSE398 Web server</em>\r\n", body);

  /* Print the HTTP response */
  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: text/html\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
  Rio_writen(fd, buf, strlen(buf));
  Rio_writen(fd, body, strlen(body));
}

/*
 * usage - explain program invocation
 */
void usage(char* progname) {
  fprintf(stderr, "usage: %s -p <port> -h -t\n", progname);
  fprintf(stderr, "   [-h will print this message and exit]\n");
  fprintf(stderr, "   [-t will run some very simple tests and exit]\n");
  exit(1);
}

/*
 * load_one - Load a single function pointer from a single .so
 */
void load_one(char *so_name, char *func_name, int index) {
  char *error;
  void *handle = dlopen(so_name, RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "Error opening %s\n", so_name);
    exit(-1);
  }
  extensions[index].func_ptr = dlsym(handle, func_name);
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "could not find %s in %s\n", func_name, so_name);
    dlclose(handle);
    exit(0);
  }
  extensions[index].os_handle = handle;
  extensions[index].pathname = so_name;
}

/*
 * init_extensions - Load the extensions that will be used by our web server
 */
void init_extensions() {
  load_one("./cgi-bin/add.so", "add_service", ADD_EXT);
  load_one("./cgi-bin/getrand.so", "getrand_service", RANDCRAWL_EXT);
  load_one("./cgi-bin/webtranslate.so", "webtranslate_service", TRANSLATE_EXT);
  load_one("./cgi-bin/counter.so", "counter_service", COUNTER_EXT);
}

/*
 * fini_extensions - close all loaded .so files.  Don't use a function
 *                   pointer after closing its so!
 */
void fini_extensions() {
  int i;
  for (i = 0; i < NUM_EXTS; ++i) {
    dlclose(extensions[i].os_handle);
    extensions[i].func_ptr = NULL;
    extensions[i].os_handle = NULL;
  }
}
