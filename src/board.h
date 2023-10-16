#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;
const int CELL_SIZE = 5;
const int BOARD_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int BOARD_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

class Board {
    private:
        bool board[BOARD_HEIGHT][BOARD_WIDTH];
        bool next_board[BOARD_HEIGHT][BOARD_WIDTH];
    public:
        Board();

        void reset();

        void update_board();

        void render_board(SDL_Renderer *renderer);

        bool get_state(int x, int y);

        int count_neighbours(int x, int y);

        bool new_state(int x, int y);
};