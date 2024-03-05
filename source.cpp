#include <array>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm> 
#include <cstdlib> 

const int SHAPE_SIZE = 4;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int BLOCK_SIZE = 30; 


const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> TETROMINO_I = { {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
} };

const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> TETROMINO_L = { {
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
} };

const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> TETROMINO_J = { {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
} };

const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> TETROMINO_O = { {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
} };

const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> TETROMINO_S = { {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
} };

const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> TETROMINO_Z = { {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
} };

const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> TETROMINO_T = { {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
} };

class Shape {
private:
    std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> matrix;

public:
    Shape(const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE>& m) : matrix(m) {}

    void rotate() {
        // Transpose the matrix
        for (int i = 0; i < SHAPE_SIZE; ++i) {
            for (int j = i + 1; j < SHAPE_SIZE; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Reverse each row for a clockwise rotation
        for (auto& row : matrix) {
            std::reverse(row.begin(), row.end());
        }
    }

    const std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE>& getMatrix() const {
        return matrix;
    }

    static std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE> getRandomShape() {
        static const std::vector<std::array<std::array<int, SHAPE_SIZE>, SHAPE_SIZE>> shapes = {
            TETROMINO_I,
            TETROMINO_J,
            TETROMINO_L,
            TETROMINO_O,
            TETROMINO_S,
            TETROMINO_T,
            TETROMINO_Z
        };

        int randomIndex = rand() % shapes.size();
        return shapes[randomIndex];
    }
};


class Piece {
private:
    Shape shape;
    sf::Vector2i position; 
    int x, y;

public:
    Piece(const Shape& s, int startX, int startY) : shape(s), x(startX), y(startY) {}

    
    void moveDown() {
        position.y += 1;
    }

    
    void moveLeft() {
        position.x -= 1;
    }

    void moveRight() {
        position.x += 1;
    }

    // Getter methods for position
    int getX() const { return position.x; }
    int getY() const { return position.y; }

    // Setter method for position
    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }
    
    void move(int dx, int dy) {
        position.x += dx;
        position.y += dy;
    }

   // void setShape(const Shape& s) {
       // shape = s;
    //}


    void rotate() {
        shape.rotate();
    }

    

    const Shape& getShape() const {
        return shape;
    }

    const sf::Vector2i& getPosition() const {
        return position;
    }
};
class Board {
private:
    std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT> grid;

public:
    Board() {
        for (auto& row : grid) {
            row.fill(0);
        }
    }
    bool tryMovePiece(Piece& piece, int newX, int newY) {
       
        if (canPlacePiece(piece, newX, newY)) {
            
            piece.setPosition(newX, newY);
            return true;
        }
        // If the new position is not valid, do not update the position
        return false;
    }
    bool canPlacePiece(const Piece& piece, int x, int y) {
        auto shape = piece.getShape().getMatrix();
        for (int i = 0; i < SHAPE_SIZE; ++i) {
            for (int j = 0; j < SHAPE_SIZE; ++j) {
                if (shape[i][j] != 0) {
                    int boardX = x + j;
                    int boardY = y + i;
                    if (boardX < 0 || boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT || grid[boardY][boardX] != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void  placePiece(const Piece& piece, int x, int y) {
        auto shapeMatrix = piece.getShape().getMatrix();
        for (int i = 0; i < SHAPE_SIZE; ++i) {
            for (int j = 0; j < SHAPE_SIZE; ++j) {
                if (shapeMatrix[i][j] != 0) {
                    grid[y + i][x + j] = 1;  // Marking the cell as occupied
                }
            }
        }
    }

    

    bool isLineComplete(int line) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (grid[line][x] == 0) {
                return false;
            }
        }
        return true;
    }

    void clearLine(int line) {
        for (int y = line; y > 0; --y) {
            for (int x = 0; x < BOARD_WIDTH; ++x) {
                grid[y][x] = grid[y - 1][x];
            }
        }
        grid[0].fill(0);
    }

    int clearCompleteLines() {
        int linesCleared = 0;
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            if (isLineComplete(y)) {
                clearLine(y);
                linesCleared++;
            }
        }
        return linesCleared; // Return the count of cleared lines
    }

    const std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT>& getGrid() const {
        return grid;
    }

};

class Game {
private:
    std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT> grid;
    sf::RenderWindow window;
    Board board;           // The game board
    Piece currentPiece;    // The current falling piece
    Piece nextPiece;       // The next piece that will come after the current one
    int score;             // The player's score

public:
    Game()
        : window(sf::VideoMode(800, 600), "Tetris"),  // Initialize the SFML window
        currentPiece(Shape(Shape::getRandomShape()), BOARD_WIDTH / 2 - SHAPE_SIZE / 2, 0),  // Initialize currentPiece
        nextPiece(Shape(Shape::getRandomShape()), BOARD_WIDTH / 2 - SHAPE_SIZE / 2, 0),  // Initialize nextPiece
        score(0) {  // Initialize score
        srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
    }


    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle keyboard events
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    // Attempt to move the piece left
                    if (board.canPlacePiece(currentPiece, currentPiece.getX() - 1, currentPiece.getY())) {
                        currentPiece.move(-1, 0); // Move left
                    }
                    break;
                case sf::Keyboard::Right:
                    // Attempt to move the piece right
                    if (board.canPlacePiece(currentPiece, currentPiece.getX() + 1, currentPiece.getY())) {
                        currentPiece.move(1, 0); // Move right
                    }
                    break;
                case sf::Keyboard::Down:
                    // Attempt to move the piece down faster
                    if (board.canPlacePiece(currentPiece, currentPiece.getX(), currentPiece.getY() + 1)) {
                        currentPiece.move(0, 1); // Move down
                    }
                    break;
                case sf::Keyboard::Up:
                    // Attempt to rotate the piece
                    // Save the original state in case we need to revert the rotation
                    Shape originalShape = currentPiece.getShape();
                    int originalX = currentPiece.getX();
                    int originalY = currentPiece.getY();

                    currentPiece.rotate(); // Perform rotation

                    // Check if the rotation is valid
                    if (!board.canPlacePiece(currentPiece, originalX, originalY)) {
                        // If not valid, revert to the original state
                        currentPiece.setShape(originalShape); // Assumes setShape() method exists
                        currentPiece.setPosition(originalX, originalY); // Assumes setPosition() method exists
                    }
                    break;
                }

            }
        }
    }

    void handleGameOver() {
        // Create a game-over message
        sf::Font font;
        if (!font.loadFromFile("Open_Sans/static/OpenSans_SemiCondensed-Regular.ttf")) {
            //std::cerr << "Failed to load font for game over screen." << std::endl;
            return; // Can't load the font, so we can't display the message
        }

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over!\nClick to exit.");
        gameOverText.setCharacterSize(30); // Example character size
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getLocalBounds().width / 2.0f,
            window.getSize().y / 2.0f - gameOverText.getLocalBounds().height / 2.0f);

        // Draw the game-over screen
        window.clear();
        window.draw(gameOverText);
        window.display();

        // Wait for a mouse click or key press before closing the window
        sf::Event event;
        while (true) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed ||
                    event.type == sf::Event::MouseButtonPressed ||
                    event.type == sf::Event::KeyPressed) {
                    window.close();
                    return; // Exit the function and close the game window
                }
            }
        }
    }



    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

   

    void update() {
        static sf::Clock clock;
        float elapsed = clock.restart().asSeconds();

        // Example logic: Move current piece down every second
        static float timeSinceLastMove = 0.0f;
        timeSinceLastMove += elapsed;

        if (timeSinceLastMove >= 1.0f) { // Adjust the timing as needed
            timeSinceLastMove = 0.0f;

            // Attempt to move the piece down
            if (!board.canPlacePiece(currentPiece, currentPiece.getX(), currentPiece.getY() + 1)) {
                board.placePiece(currentPiece, currentPiece.getX(), currentPiece.getY());

                // Check for and clear any complete lines, then update the score
                int linesCleared = board.clearCompleteLines();
                score += calculateScore(linesCleared);

                if (!board.canPlacePiece(nextPiece, BOARD_WIDTH / 2 - SHAPE_SIZE / 2, 0)) {
                    // The next piece cannot be placed at the starting position, game over
                    handleGameOver();
                    return;  // Stop the update method if the game is over
                }

                // Spawn a new piece
                currentPiece = nextPiece;
                nextPiece = Piece(Shape(Shape::getRandomShape()), BOARD_WIDTH / 2 - SHAPE_SIZE / 2, 0);
            }
            else {
                // If the piece can move down, update its position
                currentPiece.move(0, 1);
            }
        }
    }



    void drawNextPiece(const Piece& nextPiece) {
        sf::Font font;
        if (!font.loadFromFile("Open_Sans/static/OpenSans_SemiCondensed-Regular.ttf")) {
            //std::cerr << "Failed to load font for next piece preview." << std::endl;
            // Handle the error appropriately
            return;
        }

        // Define text for the label
        sf::Text label;
        label.setFont(font);
        label.setString("Next Piece:");
        label.setCharacterSize(24); // Choose an appropriate character size
        label.setFillColor(sf::Color::White); // Choose a color that stands out
        label.setPosition(BOARD_WIDTH * BLOCK_SIZE + 50, 120); // Adjust Y position to be above the next piece preview

        // Draw the label
        window.draw(label);

        // Define the position where the next piece preview will be drawn.
        // This should be offset from the main game board.
        const sf::Vector2f nextPiecePosition(BOARD_WIDTH * BLOCK_SIZE + 50, 150);

        // Draw the Tetromino blocks for the next piece
        auto shapeMatrix = nextPiece.getShape().getMatrix();
        for (int y = 0; y < SHAPE_SIZE; ++y) {
            for (int x = 0; x < SHAPE_SIZE; ++x) {
                if (shapeMatrix[y][x]) {
                    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1)); // Subtract 1 to create a small gap between blocks
                    block.setPosition(nextPiecePosition.x + x * BLOCK_SIZE, nextPiecePosition.y + y * BLOCK_SIZE);
                    block.setFillColor(sf::Color::Green); // You can choose a different color for the next piece
                    window.draw(block);
                }
            }
        }
    }



    void render() {
        window.clear();

        // Draw the board, current piece, next piece, and score
        drawBoard();
        drawPiece(currentPiece);
        drawNextPiece(nextPiece);  // You will need to implement this method
        drawScore();

        window.display();
    }

    void drawBoard() {
        auto& grid = board.getGrid();
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            for (int x = 0; x < BOARD_WIDTH; ++x) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                block.setFillColor(grid[y][x] != 0 ? sf::Color::Blue : sf::Color::Transparent); // Fill color if occupied
                window.draw(block);
            }
        }
        
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            for (int x = 0; x < BOARD_WIDTH; ++x) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1)); // Subtracting 1 for grid lines
                block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                block.setFillColor(grid[y][x] == 1 ? sf::Color::Blue : sf::Color::Transparent); // Fill color if occupied
                window.draw(block);
            }
        }

        // Drawing the grid lines
        for (int y = 0; y <= BOARD_HEIGHT; ++y) {
            sf::RectangleShape horizontalLine(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, 1)); // Horizontal line
            horizontalLine.setPosition(0, y * BLOCK_SIZE);
            horizontalLine.setFillColor(sf::Color::White); // White color for grid line
            window.draw(horizontalLine);
        }

        for (int x = 0; x <= BOARD_WIDTH; ++x) {
            sf::RectangleShape verticalLine(sf::Vector2f(1, BOARD_HEIGHT * BLOCK_SIZE)); // Vertical line
            verticalLine.setPosition(x * BLOCK_SIZE, 0);
            verticalLine.setFillColor(sf::Color::White); // White color for grid line
            window.draw(verticalLine);
        }
    }




    void drawPiece(const Piece& piece) {
        auto shapeMatrix = piece.getShape().getMatrix();
        auto position = piece.getPosition();

        for (int y = 0; y < SHAPE_SIZE; ++y) {
            for (int x = 0; x < SHAPE_SIZE; ++x) {
                if (shapeMatrix[y][x]) {
                    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                    block.setPosition((position.x + x) * BLOCK_SIZE, (position.y + y) * BLOCK_SIZE);
                    block.setFillColor(sf::Color::Red); // Color of the Tetris piece
                    block.setOutlineColor(sf::Color::Black);
                    block.setOutlineThickness(-1);
                    window.draw(block);
                }
            }
        }
    }

    void drawScore() {
        sf::Font font;
        if (!font.loadFromFile("Open_Sans/static/OpenSans_SemiCondensed-Regular.ttf")) {
            // Print an error message to the console
            return; // Exit the function if the font can't be loaded
        }

        sf::Text text;
        text.setFont(font);
        text.setString("Score: " + std::to_string(score));
        text.setCharacterSize(24); // Example character size
        text.setFillColor(sf::Color::White); // Change color to white for visibility
        text.setPosition(320, BOARD_HEIGHT * BLOCK_SIZE - 50); // Adjust Y position so it's above the bottom

        window.draw(text);
    }

    int calculateScore(int linesCleared) {
        const int singleLineScore = 100;
        const int doubleLineScore = 300;
        const int tripleLineScore = 500;
        const int tetrisScore = 800; // Clearing four lines at once

        switch (linesCleared) {
        case 1: return singleLineScore;
        case 2: return doubleLineScore;
        case 3: return tripleLineScore;
        case 4: return tetrisScore;
        default: return 0;
        }
    }


};
int main() {
    Game tetrisGame;
    tetrisGame.run();
    return 0;
}