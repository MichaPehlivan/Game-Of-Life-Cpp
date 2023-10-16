#include <iostream>
#include "board.h"

Board::Board() {
    srand(time(0));
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            board[j][i] = std::rand() % 2;
        }
    }           
}

void Board::reset() {
    srand(time(0));
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            board[j][i] = std::rand() % 2;
        }
    }
}

void Board::update_board() {
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            next_board[j][i] = new_state(i, j);
        }
    }

    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            board[j][i] = next_board[j][i];
        }
    }
}

void Board::render_board(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            if(get_state(i, j)) {
                SDL_Rect rect;
                rect.x = i*CELL_SIZE;
                rect.y = j*CELL_SIZE;
                rect.w = CELL_SIZE;
                rect.h = CELL_SIZE;

                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

bool Board::get_state(int x, int y) {
    if(x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return false;
    }
    return board[y][x];
}

int Board::count_neighbours(int x, int y) {
    int count = 0;
    for(int i = x-1; i <= x+1; i++) {
        for(int j = y-1; j <= y+1; j++) {
            if(!(i == x && j == y) && get_state(i, j)) {
                count++;
            }
        }
    }
    return count;
}

bool Board::new_state(int x, int y) {
    int neighbours_alive = count_neighbours(x, y);
    
    if(get_state(x, y)) {
        if(neighbours_alive == 2 || neighbours_alive == 3) {
            return true;
        }
    }
    else {
        if(neighbours_alive == 3) {
            return true;
        }
    }
    return false;
}
