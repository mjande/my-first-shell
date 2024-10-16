#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util/gprintf.h"

#include "signal.h"

static void
interrupting_signal_handler(int signo)
{
  /* Its only job is to interrupt system calls--like read()--when
   * certain signals arrive--like Ctrl-C.
   */
}

static struct sigaction ignore_action = {.sa_handler = SIG_IGN},
                        interrupt_action = {.sa_handler =
                                                interrupting_signal_handler},
                        old_sigtstp, old_sigint, old_sigttou;

/* Ignore certain signals.
 * 
 * @returns 0 on succes, -1 on failure
 *
 *
 * The list of signals to ignore:
 *   - SIGTSTP
 *   - SIGINT
 *   - SIGTTOU
 *
 * Should be called immediately on entry to main() 
 *
 * Saves old signal dispositions for a later call to signal_restore()
 */
int
signal_init(void)
{
  /* Initialize signals, store old actions (MA) 
   *
   * e.g. sigaction(SIGNUM, &new_handler, &saved_old_handler);
   *
   * */
  int res = sigaction(SIGTSTP, &ignore_action, &old_sigtstp);
  if (res == -1) {
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }

  res = sigaction(SIGINT, &ignore_action, &old_sigint);
  if (res == -1) {
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }

  res = sigaction(SIGTTOU, &ignore_action, &old_sigttou);
  if (res == -1) {
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }

  return 0;
}

/** enable signal to interrupt blocking syscalls (read/getline, etc) 
 *
 * @returns 0 on succes, -1 on failure
 *
 * does not save old signal disposition
 */
int
signal_enable_interrupt(int sig)
{
  /* Set the signal disposition for signal to interrupt (MA) */
  int res = sigaction(sig, &interrupt_action, NULL);

  if (res == -1) {
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }
  return 0;
}

/** ignore a signal
 *
 * @returns 0 on success, -1 on failure
 *
 * does not save old signal disposition
 */
int
signal_ignore(int sig)
{
  /* Set the signal to be ignored (MA) */
  int res = sigaction(sig, &ignore_action, NULL); 

  if (res == -1) { 
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }
  return 0;
}

/** Restores signal dispositions to what they were when myfirstshell was invoked
 *
 * @returns 0 on success, -1 on failure
 *
 */
int
signal_restore(void)
{
  /* Restore old actions (MA)
   *
   * e.g. sigaction(SIGNUM, &saved_old_handler, NULL);
   *
   * */
  int res = sigaction(SIGTSTP, &old_sigtstp, NULL);
  if (res == -1) {
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }

  res = sigaction(SIGINT, &old_sigint, NULL);
  if (res == -1) {
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }

  res = sigaction(SIGTTOU, &old_sigttou, NULL);
  if (res == -1) {
    gprintf("Signal error: %s", strerror(errno)); 
    return -1;
  }

  return 0;
}
