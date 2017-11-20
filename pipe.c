#include <stdio.h>
#include <unistd.h>

int main() {
  int READ = 0;
  int WRITE = 1;

  int f;

  int child_read[2];
  int child_write[2];

  pipe(child_read);
  pipe(child_write);

  f = fork();

  if (f) {
    close(child_read[READ]);
    close(child_write[WRITE]);

    int a = 100;
    int b;

    printf("[parent] wrote %d to child\n", a);
    write(child_read[WRITE], &a, sizeof(a));

    read(child_write[READ], &b, sizeof(b));
    printf("[parent] read %d from child\n", b);
  } else {
    close(child_read[WRITE]);
    close(child_write[READ]);

    int a;

    read(child_read[READ], &a, sizeof(a));
    printf("[child] read %d from parent\n", a);

    a *= 2;
    printf("[child] wrote %d to parent\n", a);
    write(child_write[WRITE], &a, sizeof(a));
  }

  return 0;
}
