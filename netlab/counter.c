/*
 * counter.c - a function that extracts one integer from a query string,
 *             opens a file, reads an integer from that file, adds the query
 *             string's integer to that integer, and writes the new value to
 *             the file.  The new value should also be returned as a web
 *             page.
 *
 *             query string parameters: increment
 */
#include "csapp.h"

#define FILENAME "COUNT"
#define FILEPATH "cgi-bin/"
static int gdfd;

void open_file();
void close_file();

int counter_service(char *querystring, int fd) {
  char buf[MAXLINE], *p;
  char arg1[MAXLINE], content[MAXLINE] ;
  char buf2[MAXLINE], temp[MAXLINE], temp2[MAXLINE];
  int input = 7;
  int n2 = 8;
  
  // parse out args
  strncpy(buf, querystring, MAXLINE);
  //check argname
  p = strstr(buf, "increment");
  if(p == NULL)
  {
    sprintf(content, "<html><head><title>Mike</title></head><body>\r\n");
    sprintf(content, "%s%s", content, "Enter increment");
    sprintf(content, "%s%s", content, "\r\n</body></html>\r\n");
  
    sprintf(buf2, "Content-length: %d\r\n", (int)strlen(content));
    sprintf(buf2, "%s%s%s", buf2, "Content-type: text/html\r\n\r\n", content);
    Rio_writen(fd, buf2, (int) strlen(buf2)); 
  }
  p = strchr(buf, '&');
  *p = '\0';
  strcpy(arg1, buf);
  char *a1 = arg1;
  while (*a1 != '='){
    a1++;
  }
  a1++;
  if( (*a1 >= '0' && *a1<= '9') || (*a1 == '-') )
  {
    input = atoi(a1);

    // reset file
    lseek(gdfd, 0, SEEK_SET);
    read(gdfd, temp, MAXLINE);
    char *t1 = temp;
    n2 = atoi(t1);

    int n3 = n2 + input;
    sprintf(temp2, "%d", n3);
    lseek(gdfd,0,SEEK_SET);
    //rewrite file
    write(gdfd, temp2, (int)strlen(temp2));

    sprintf(content, "<html><head><title>Mike</title></head><body>\r\n");
    sprintf(content, "%s%s", content, temp2);
    sprintf(content, "%s%s", content, "\r\n</body></html>\r\n");

    sprintf(buf2, "Content-length: %d\r\n", (int)strlen(content));
    sprintf(buf2, "%s%s%s", buf2, "Content-type: text/html\r\n\r\n", content);
    Rio_writen(fd, buf2, (int) strlen(buf2));
  }
  else
  {
    sprintf(content, "<html><head><title>Mike</title></head><body>\r\n");
    sprintf(content, "%s%s", content, "Enter a valid integer");
    sprintf(content, "%s%s", content, "\r\n</body></html>\r\n");

    sprintf(buf2, "Content-length: %d\r\n", (int)strlen(content));
    sprintf(buf2, "%s%s%s", buf2, "Content-type: text/html\r\n\r\n", content);
    Rio_writen(fd, buf2, (int) strlen(buf2));	
  }
  return 0;
}

/*
 * you should open the COUNT file once, here, so that the file is open for
 * as long as this .so is loaded.
 */
__attribute__((constructor))
void open_file() {
  gdfd = open("cgi-bin/COUNT", O_RDWR);
}

/*
 * likewise, you should close the COUNT file once, here
 */
__attribute__((destructor))
void close_file() {
  close(gdfd);
}
