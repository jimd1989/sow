#include <err.h>
#include <sndio.h>

#define SIO_HANDLES_COUNT 16

typedef struct sio_hdl* Sio;

static Sio SIO_HANDLES[SIO_HANDLES_COUNT] = {0};

int start_audio(int n) {
  int m = n - 1;
  if (n < 1 || n > SIO_HANDLES_COUNT) {
    warnx("select an audio handle between 1 – %d", SIO_HANDLES_COUNT);
    return -1;
  }
  /* init here */
  return m;
}
