#include "matrix.h"
#include <vector>
#include <iostream>


int main() {
    {
        std::cout << "test 1: print\n\n";

        // MatrixAlgebra::Matrix<int> m({ MatrixAlgebra::AVector<int> ({ 1, 2, 3 }, 3), 
        //                                MatrixAlgebra::AVector<int> ({ 4, 5, 6 }, 3),
        //                                MatrixAlgebra::AVector<int> ({ 7, 8, 9 }, 3) }, 
        //                                3, 3);

        MatrixAlgebra::Matrix<int> m({ { 1, 2, 3 },
                                       { 4, 5, 6 },
                                       { 7, 8, 9 } }, 3, 3);

        std::cout << m;
    }

    std::cout << "\n\n\n";

    {
        std::cout << "test 2: sum\n\n";

        MatrixAlgebra::Matrix<int> a({ { 1, 0, 0 },
                                       { 0, 2, 0 },
                                       { 0, 0, 3 } }, 3, 3);

        MatrixAlgebra::Matrix<int> b({ { 0, 0, 3 },
                                       { 0, 2, 0 },
                                       { 1, 0, 0 } }, 3, 3);

        std::cout << a + b;
    }

    std::cout << "\n\n\n";

    {
        std::cout << "test 3: diff\n\n";

        MatrixAlgebra::Matrix<int> a({ { 1, 0, 0 },
                                       { 0, 2, 0 },
                                       { 0, 0, 3 } }, 3, 3);

        MatrixAlgebra::Matrix<int> b({ { 0, 0, 3 },
                                       { 0, 2, 0 },
                                       { 1, 0, 0 } }, 3, 3);

        std::cout << a - b;
    }

    std::cout << "\n\n\n";

    {
        std::cout << "test 4: m * num\n\n";

        MatrixAlgebra::Matrix<int> m({ { 1, 2, 3 },
                                       { 4, 5, 6 },
                                       { 7, 8, 9 } }, 3, 3);

        std::cout << m * 3 << "\n";
        std::cout << 3 * m;
    }

    std::cout << "\n\n\n";

    {
        std::cout << "test 5: matrix multiplication\n\n";

        MatrixAlgebra::Matrix<int> a({ { 1, 2, 3, 4 },
                                       { 0, 0, 0, 0 },
                                       { 0, 0, 0, 0 } }, 3, 4);

        MatrixAlgebra::Matrix<int> b({ { 1, 0, 0 },
                                       { 2, 0, 0 },
                                       { 3, 0, 0 },
                                       { 4, 0, 0 } }, 4, 3);

        std::cout << a * b;
    }
}