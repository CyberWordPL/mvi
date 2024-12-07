#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orginal_termios;

void enable_raw_mode() {
    struct termios raw_termios = orginal_termios;
    
    raw_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw_termios.c_oflag &= ~(OPOST);
    raw_termios.c_cflag |= CS8;
    raw_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw_termios.c_cc[VMIN] = 0;
    raw_termios.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orginal_termios);
}

void switch_to_alternate_screen() {
    printf("\033[?1049h");
}

void switch_from_alternate_screen() {
    printf("\033[?1049l");
}

void deinit_terminal() {
    disable_raw_mode();
    switch_from_alternate_screen();
}

void init_terminal() {
    atexit(deinit_terminal);

    // Get orginal termios
    tcgetattr(STDIN_FILENO, &orginal_termios);
    
    enable_raw_mode();
    switch_to_alternate_screen();
}
