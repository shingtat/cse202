/*
 * getrand.c - a function that extracts one integer from a query string, uses
 *             it as the seed when executing a call to rand_r, and writes the
 *             resulting random number and seed to a file descriptor as a web
 *             page
 *
 *             query string parameters: seed
 */
#include "csapp.h"

int getrand_service(char *querystring, int fd) {
  char buf[MAXLINE], *p;
  char arg1[MAXLINE], content[MAXLINE];
  char buf2[MAXLINE];
  int input = 3;
  unsigned int seed;
  int random_num, new_seed;

  //check argname
  strncpy(buf, querystring, MAXLINE);
  p = strstr(buf, "seed");
  if(p == NULL)
  {
    sprintf(content, "<html><head><title>Mike</title></head><body>\r\n");
    sprintf(content, "%s%s", content, "Enter a seed");
    sprintf(content, "%s%s", content, "\r\n</body></html>\r\n");
  
    sprintf(buf2, "Content-length: %d\r\n", (int)strlen(content));
    sprintf(buf2, "%s%s%s", buf2, "Content-type: text/html\r\n\r\n", content);
    Rio_writen(fd, buf2, (int) strlen(buf2)); 
  }
  //parse arg
  p = strchr(buf, '&');
  *p = '\0';
  strcpy(arg1, buf);
  char *a1 = arg1;
  while (*a1 != '='){
    a1++;
  }
  a1++;
  char* check = a1;
  if( (*check >= '0' && *check <= '9') || (*check == '-') )
  {
    input = atoi(a1);
    seed = (unsigned int) input;
    // were told to do twice by reference
    random_num = rand_r(&seed);
    new_seed = rand_r(&seed);
	
    sprintf(content, "<html><head><title>Mike</title></head><body>\r\n");
    sprintf(content, "%s(%d, %d)", content, random_num, new_seed);
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
