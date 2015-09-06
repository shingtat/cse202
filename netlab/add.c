/*
 * add.c - a function that extracts two integers from a query string, adds
 *         them, and writes the result to a file descriptor
 *
 *         query string parameters: n1, n2
 */
#include "csapp.h"

int add_service(char *querystring, int fd) {
  char buf[MAXLINE], *p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  char buf2[MAXLINE];
  int n1=0, n2=0;

  /* copy query string to buf */
  strncpy(buf, querystring, MAXLINE);

  /*
   * this is a really bad way to parse the query string... your code should
   * be more careful
   */
  p = strchr(buf, '&');
  *p = '\0';
  strcpy(arg1, buf);
  strcpy(arg2, p+1);
  char* a1 = arg1;
  char* a2 = arg2;
  while(*a1 != '=') a1++;
  a1++;
  n1 = atoi(a1);
  while(*a2 != '=') a2++;
  a2++;
  n2 = atoi(a2);

  /* Make the response body */
  sprintf(content, "<html><head><title>Result</title></head><body>\r\n");
  sprintf(content, "%s%d", content, n1 + n2);
  sprintf(content, "%s%s", content, "\r\n</body></html>\r\n");

  /* Generate the HTTP response, write to fd */
  sprintf(buf2, "Content-length: %d\r\n", (int)strlen(content));
  sprintf(buf2, "%s%s%s", buf2, "Content-type: text/html\r\n\r\n", content);
  Rio_writen(fd, buf2, (int)strlen(buf2));
  return 0;
}
