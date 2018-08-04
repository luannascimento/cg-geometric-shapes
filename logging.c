#include "libs/headers.h"

#define FILELOG "log.txt"
FILE* fp = NULL;

static void initLog ();
static void finallyLog ();
static void writeLog (const char* fmt, ...);

void logging (const char* fmt, ...)
{
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  char time_buf[100];
  strftime(time_buf, sizeof(time_buf), "%D %T", gmtime(&ts.tv_sec));

  va_list list_arg;
  char buffer[BUFSIZ];
  va_start(list_arg, fmt);
  vsnprintf(buffer, BUFSIZ, fmt, list_arg);
  va_end(list_arg);

  initLog();
  writeLog("%s [debug]: %s",time_buf, buffer);
  finallyLog();
}

static void initLog ()
{
  fp = fopen(FILELOG,"at");
  if(!fp)
  {
    exit(EXIT_FAILURE);
  }
}

static void finallyLog ()
{
  fclose(fp);
}

static void writeLog (const char* fmt, ...)
{
  va_list list_arg;
  char buffer[BUFSIZ];
  va_start(list_arg, fmt);
  vsnprintf(buffer, BUFSIZ, fmt, list_arg);
  va_end(list_arg);

  fprintf(fp,"%s", buffer);
}