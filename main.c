#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uv.h>
#include <ncurses.h>

static char input_buffer[128];


#define CORPS_SNAKE '-';
#define TETE_SNAKE 'B'
#define NOURRITURE '*'
#define CASE_VIDE ' '


char ** grille = NULL;
int nbLignes = 0;
int nbColonnes = 0;
int modeEvolueDansLequelLeSerpent = 0;

struct uneCellule {
  int ligne;
  int colonne;
  struct uneCellule * suiv;
};
typedef struct uneCellule uneCellule;

struct unSnake {
  uneCellule * teteSnake;
  uneCellule * queueSnake;
};
typedef struct unSnake unSnake;

struct uneDirection {
  int ligne;
  int colonne;
};
typedef struct uneDirection uneDirection;

unSnake creerSnake() {

  unSnake snake;

  uneCellule * teteSnake = malloc(sizeof(uneCellule));
  uneCellule * queueSnake = malloc(sizeof(uneCellule));
  uneCellule * milieuSnake = malloc(sizeof(uneCellule));

  teteSnake->ligne = 1;
  teteSnake->colonne = 4;
  teteSnake->suiv = NULL;

  milieuSnake->ligne = 1;
  milieuSnake->colonne = 3;
  milieuSnake->suiv = teteSnake;

  queueSnake->ligne = 1;
  queueSnake->colonne = 2;
  queueSnake->suiv = milieuSnake;

  snake.teteSnake = teteSnake;
  snake.queueSnake = queueSnake;

  return snake;
}
 
 


void timer_cb(uv_timer_t *handle) { printf("hello"); }

void alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  buf->base = input_buffer;
  buf->len = sizeof(input_buffer);
}

void read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
  if (nread > 0 && buf != NULL) {
    printf("%s\n", buf->base);

    if (buf->base[0] == 'q') {
      uv_stop(stream->data);
    }
  }
}

int main() {
  uv_loop_t *loop = malloc(sizeof(uv_loop_t));
  uv_loop_init(loop);

  uv_timer_t timer_req;
  uv_tty_t input_tty;

  uv_timer_init(loop, &timer_req);
  uv_timer_start(&timer_req, timer_cb, 5000, 2000);

  uv_tty_init(loop, &input_tty, STDIN_FILENO, 0);
  uv_tty_set_mode(&input_tty, UV_TTY_MODE_RAW);
  input_tty.data = loop;
  int user_input = getchar();

  uv_read_start((uv_stream_t *)&input_tty, alloc_cb, read_cb);

  uv_run(loop, UV_RUN_DEFAULT);
  uv_loop_close(loop);

  uv_tty_reset_mode();
  free(loop);
  return 0;
 }
