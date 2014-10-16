/* header file for queue operations
 * the file is used in boss-worker.c and pipeline.c
 * see Thread Time: The Multithreaded Programming Guide
 * Scott J.Norton and Mark D.DiPasquale
 * 1997, Prentice Hall (www.prenhall.com)
 * ISBN: 0-13-190067-6
 * adapted by Bogdan Costinescu, march 1999
 */

/*
 * work structure which is placed on the queue and later processed by 
 * the worker threads. This data structure should contain all the 
 * necessary information for the worker to process the request.
 */
struct q_work_struct {
  struct q_work_struct *next;
  int req_type;

  /* place application specific task data here */
  int line;


};

/* queue data structure passed to the queue management functions */
#define QUEUE_VALID 5678

struct queue_struct {
  int valid;
  pthread_mutex_t qlock;
  pthread_cond_t boss_cv;
  pthread_cond_t worker_cv;
  int qexit;
  int boss_waiting;
  int worker_waiting;
  int queue_len;
  int max_queue_len;
  struct q_work_struct *head;
  struct q_work_struct *tail;
};


int queue_init(struct queue_struct *queue, int max_len);
int enqueue(struct queue_struct *queue, struct q_work_struct *elem);
struct q_work_struct * dequeue(struct queue_struct *queue);
