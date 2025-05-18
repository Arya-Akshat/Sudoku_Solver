
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <vector>
#include <array>
#include <QWidget>

class SudokuGame : public QWidget {
    Q_OBJECT

public:
    SudokuGame(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Sudoku Game");
        resize(500, 600);

        // Initialize puzzle levels
        sudokuLevels = {
                    // Level 1
                    {{{5, 3, 0, 0, 7, 0, 0, 0, 0},
                      {6, 0, 0, 1, 9, 5, 0, 0, 0},
                      {0, 9, 8, 0, 0, 0, 0, 6, 0},
                      {8, 0, 0, 0, 6, 0, 0, 0, 3},
                      {4, 0, 0, 8, 0, 3, 0, 0, 1},
                      {7, 0, 0, 0, 2, 0, 0, 0, 6},
                      {0, 6, 0, 0, 0, 0, 2, 8, 0},
                      {0, 0, 0, 4, 1, 9, 0, 0, 5},
                      {0, 0, 0, 0, 8, 0, 0, 7, 9}}},
                    // Level 2
                    {{{2, 0, 0, 0, 9, 0, 0, 0, 1},
                      {0, 0, 7, 4, 0, 0, 0, 3, 0},
                      {5, 0, 0, 0, 0, 0, 8, 0, 0},
                      {0, 0, 0, 1, 7, 0, 0, 0, 4},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {8, 0, 0, 0, 2, 3, 0, 0, 0},
                      {0, 0, 5, 0, 0, 0, 0, 0, 8},
                      {0, 9, 0, 0, 0, 5, 6, 0, 0},
                      {4, 0, 0, 0, 3, 0, 0, 0, 9}}},
                    // Level 3
                    {{{1, 0, 0, 0, 0, 7, 0, 9, 0},
                      {0, 3, 0, 0, 2, 0, 0, 0, 8},
                      {0, 0, 9, 6, 0, 0, 5, 0, 0},
                      {0, 0, 5, 3, 0, 0, 9, 0, 0},
                      {0, 1, 0, 0, 8, 0, 0, 0, 2},
                      {6, 0, 0, 0, 0, 4, 0, 0, 0},
                      {3, 0, 0, 0, 0, 0, 0, 1, 0},
                      {0, 4, 1, 0, 0, 0, 0, 0, 7},
                      {0, 0, 7, 0, 0, 0, 3, 0, 0}}},
                    // Level 4
                    {{{0, 0, 0, 0, 6, 0, 0, 0, 3},
                      {0, 0, 0, 5, 0, 9, 0, 0, 0},
                      {3, 0, 0, 7, 0, 0, 0, 0, 0},
                      {0, 4, 0, 0, 0, 0, 0, 9, 0},
                      {0, 0, 8, 0, 0, 0, 1, 0, 0},
                      {0, 2, 0, 0, 0, 0, 0, 3, 0},
                      {0, 0, 0, 0, 0, 7, 0, 0, 2},
                      {0, 0, 0, 4, 0, 5, 0, 0, 0},
                      {1, 0, 0, 0, 8, 0, 0, 0, 0}}},
                    };

        // Initialize solved levels
        solvedLevels = {
        // Solution for Level 1
        {{{5, 3, 4, 6, 7, 8, 9, 1, 2},
          {6, 7, 2, 1, 9, 5, 3, 4, 8},
          {1, 9, 8, 3, 4, 2, 5, 6, 7},
          {8, 5, 9, 7, 6, 1, 4, 2, 3},
          {4, 2, 6, 8, 5, 3, 7, 9, 1},
          {7, 1, 3, 9, 2, 4, 8, 5, 6},
          {9, 6, 1, 5, 3, 7, 2, 8, 4},
          {2, 8, 7, 4, 1, 9, 6, 3, 5},
          {3, 4, 5, 2, 8, 6, 1, 7, 9}}},
        // Solution for Level 2
       {{{2, 3, 4, 7, 9, 8, 5, 6, 1},
        {1, 8, 7, 4, 5, 6, 9, 3, 2},
        {5, 6, 9, 3, 1, 2, 8, 4, 7},
        {6, 5, 2, 1, 7, 9, 3, 8, 4},
        {9, 7, 3, 5, 8, 4, 1, 2, 6},
        {8, 4, 1, 6, 2, 3, 7, 9, 5},
        {3, 2, 5, 9, 6, 1, 4, 7, 8},
        {7, 9, 8, 2, 4, 5, 6, 1, 3},
        {4, 1, 6, 8, 3, 7, 2, 5, 9}}},

        // Solution for Level 3
            {{{1, 6, 2, 8, 5, 7, 4, 9, 3},
            {5, 3, 4, 1, 2, 9, 6, 7, 8},
            {7, 8, 9, 6, 4, 3, 5, 2, 1},
            {4, 7, 5, 3, 1, 2, 9, 8, 6},
            {9, 1, 3, 5, 8, 6, 7, 4, 2},
            {6, 2, 8, 7, 9, 4, 1, 3, 5},
            {3, 5, 6, 4, 7, 8, 2, 1, 9},
            {2, 4, 1, 9, 3, 5, 8, 6, 7},
            {8, 9, 7, 2, 6, 1, 3, 5, 4}}}, 

        // Solution for Level 4
            {{{2, 1, 5, 8, 6, 4, 9, 7, 3},
              {4, 6, 7, 5, 3, 9, 2, 1, 8},
              {3, 8, 9, 7, 1, 2, 4, 5, 6},
              {6, 4, 3, 2, 5, 1, 8, 9, 7},
              {5, 9, 8, 3, 7, 6, 1, 2, 4},
              {7, 2, 1, 9, 4, 8, 6, 3, 5},
              {8, 3, 4, 1, 9, 7, 5, 6, 2},
              {9, 7, 6, 4, 2, 5, 3, 8, 1},
              {1, 5, 2, 6, 8, 3, 7, 4, 9}}}
            };

        layout = new QGridLayout(this);
        levelSelect = new QComboBox(this);

        for (int i = 1; i <= static_cast<int>(sudokuLevels.size()); ++i)
            levelSelect->addItem("Level " + QString::number(i));

        layout->addWidget(levelSelect, 0, 0, 1, 9);

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                grid[row][col] = new QLineEdit(this);
                grid[row][col]->setAlignment(Qt::AlignCenter);
                grid[row][col]->setMaxLength(1);
                grid[row][col]->setFixedSize(40, 40);

                // Add 3x3 Block Borders
                QString borderStyle = "border: 1px solid black;";
                if ((row + 1) % 3 == 0 && row != 8)
                    borderStyle += "border-bottom: 2px solid black;";
                if ((col + 1) % 3 == 0 && col != 8)
                    borderStyle += "border-right: 2px solid black;";
                grid[row][col]->setStyleSheet(borderStyle);

                layout->addWidget(grid[row][col], row + 1, col);

                connect(grid[row][col], &QLineEdit::textChanged, [=]() {
                    grid[row][col]->setStyleSheet(borderStyle);
                });
            }
        }

        QPushButton *loadButton = new QPushButton("Load Puzzle", this);
        QPushButton *checkButton = new QPushButton("Check Solution", this);
        QPushButton *clearButton = new QPushButton("Clear Board", this);
        QPushButton *hintButton = new QPushButton("Get Hint", this);

        layout->addWidget(loadButton, 10, 0, 1, 2);
        layout->addWidget(checkButton, 10, 2, 1, 2);
        layout->addWidget(clearButton, 10, 4, 1, 2);
        layout->addWidget(hintButton, 10, 6, 1, 2);

        connect(loadButton, &QPushButton::clicked, this, &SudokuGame::loadPuzzle);
        connect(checkButton, &QPushButton::clicked, this, &SudokuGame::checkSolution);
        connect(clearButton, &QPushButton::clicked, this, &SudokuGame::clearBoard);
        connect(hintButton, &QPushButton::clicked, this, &SudokuGame::showHint);
    }

private slots:
    void loadPuzzle() {
        int level = levelSelect->currentIndex();
        if (level < 0 || level >= static_cast<int>(sudokuLevels.size())) return;

        auto puzzle = sudokuLevels[level];
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (puzzle[row][col] != 0) {
                    grid[row][col]->setText(QString::number(puzzle[row][col]));
                    grid[row][col]->setReadOnly(true);
                    grid[row][col]->setStyleSheet("background-color: #e0e0e0; border: 1px solid black;");
                } else {
                    grid[row][col]->clear();
                    grid[row][col]->setReadOnly(false);
                    grid[row][col]->setStyleSheet("border: 1px solid black;");
                }
            }
        }
    }

    void checkSolution() {
        int level = levelSelect->currentIndex();
        if (level < 0 || level >= static_cast<int>(solvedLevels.size())) return;

        bool isCorrect = true;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                QString input = grid[row][col]->text();
                int expected = solvedLevels[level][row][col];
                if (input.isEmpty() || input.toInt() != expected || expected == 0) {
                    grid[row][col]->setStyleSheet("background-color: #ffcccc; border: 1px solid black;");
                    isCorrect = false;
                } else {
                    // Reset correct cells to normal style (to avoid red highlight after re-check)
                    QString borderStyle = "border: 1px solid black;";
                    if ((row + 1) % 3 == 0 && row != 8) borderStyle += "border-bottom: 2px solid black;";
                    if ((col + 1) % 3 == 0 && col != 8) borderStyle += "border-right: 2px solid black;";
                    grid[row][col]->setStyleSheet(borderStyle);
                }
            }
        }
        if (isCorrect) {
            QMessageBox::information(this, "Success", "Congratulations! You solved it correctly.");
        } else {
            QMessageBox::warning(this, "Incorrect Solution", "Some cells are incorrect. Please review.");
        }
    }

    void clearBoard() {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (!grid[row][col]->isReadOnly()) {
                    grid[row][col]->clear();
                    grid[row][col]->setStyleSheet("border: 1px solid black;");
                }
            }
        }
    }

    void showHint() {
        int level = levelSelect->currentIndex();
        if (level < 0 || level >= static_cast<int>(solvedLevels.size()))
            return;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (grid[row][col]->text().isEmpty()) {
                    int correctValue = solvedLevels[level][row][col];
                    if (correctValue != 0) {
                        grid[row][col]->setText(QString::number(correctValue));
                        grid[row][col]->setStyleSheet("background-color: #ccffcc; border: 1px solid black;");
                        return;
                    }
                }
            }
        }
    }

private:
    QGridLayout *layout;
    QComboBox *levelSelect;
    QLineEdit *grid[9][9];
    std::vector<std::array<std::array<int, 9>, 9>> sudokuLevels;
    std::vector<std::array<std::array<int, 9>, 9>> solvedLevels;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SudokuGame window;
    window.show();
    return app.exec();
}

#include "main.moc"

