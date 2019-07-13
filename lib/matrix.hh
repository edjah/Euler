#pragma once
#include <stdexcept>
#include "utility.hh"

constexpr size_t STRASSEN_CUTOFF = 128;

class Matrix {
  public:
    Matrix() {}
    Matrix(size_t nrows, size_t ncols);

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);

    Matrix(const Matrix& other) {
        *this = other;
    }

    Matrix(Matrix&& other) {
        *this = std::move(other);
    }

    ~Matrix() {
        delete[] allocation_;
        delete[] data_;
    }

    inline int64_t* operator[](size_t row) const {
        return data_[row];
    }

    inline size_t nrows() const {
        return nrows_;
    }

    inline size_t ncols() const {
        return ncols_;
    }

    inline Matrix slice(size_t y1, size_t y2, size_t x1, size_t x2) const;
    inline std::string to_string() const;
    inline Matrix mm(const Matrix& other) const;



    // Basic Arithmetic Operations
    #define matrix_matrix_arithmetic_operator_mutate(op)                    \
        inline Matrix& operator op (const Matrix& other) {                  \
            if (nrows_ != other.nrows_ || ncols_ != other.ncols_) {         \
                throw std::runtime_error("Matrix shapes do not align");     \
            }                                                               \
                                                                            \
            for (size_t i = 0, total = total_elements(); i < total; ++i) {  \
                allocation_[i] op other.allocation_[i];                     \
            }                                                               \
                                                                            \
            return *this;                                                   \
        }

    matrix_matrix_arithmetic_operator_mutate(+=);
    matrix_matrix_arithmetic_operator_mutate(-=);
    matrix_matrix_arithmetic_operator_mutate(*=);
    matrix_matrix_arithmetic_operator_mutate(/=);
    matrix_matrix_arithmetic_operator_mutate(%=);


    #define matrix_int_arithmetic_operator_mutate(op)                       \
        inline Matrix& operator op(int64_t n) {                             \
            for (size_t i = 0, total = total_elements(); i < total; ++i) {  \
                allocation_[i] op n;                                        \
            }                                                               \
            return *this;                                                   \
        }

    matrix_int_arithmetic_operator_mutate(+=);
    matrix_int_arithmetic_operator_mutate(-=);
    matrix_int_arithmetic_operator_mutate(*=);
    matrix_int_arithmetic_operator_mutate(/=);
    matrix_int_arithmetic_operator_mutate(%=);


    #define matrix_generic_arithmetic_operator_new_copy(op)                 \
        template <typename T>                                               \
        inline Matrix operator op(const T& other) const {                   \
            Matrix copy = *this;                                            \
            copy op##= other;                                               \
            return copy;                                                    \
        }

    matrix_generic_arithmetic_operator_new_copy(+);
    matrix_generic_arithmetic_operator_new_copy(-);
    matrix_generic_arithmetic_operator_new_copy(*);
    matrix_generic_arithmetic_operator_new_copy(/);
    matrix_generic_arithmetic_operator_new_copy(%);


    #define matrix_generic_arithmetic_operator_mutate_named(name, op)       \
        template <typename T>                                               \
        inline Matrix name(const T& other) {                                \
            return (*this op other);                                        \
        }                                                                   \

    matrix_generic_arithmetic_operator_mutate_named(add, +=);
    matrix_generic_arithmetic_operator_mutate_named(sub, -=);
    matrix_generic_arithmetic_operator_mutate_named(mul, *=);
    matrix_generic_arithmetic_operator_mutate_named(div, /=);
    matrix_generic_arithmetic_operator_mutate_named(mod, %=);

  private:
    inline void reallocate();

    static Matrix mm_naive(Matrix& res, const Matrix& a, const Matrix& b);
    static Matrix mm_strassen(Matrix& res, const Matrix& a, const Matrix& b);

    inline const size_t total_elements() const {
        return nrows_ * ncols_;
    }

    size_t nrows_ = 0;
    size_t ncols_ = 0;
    int64_t** data_ = nullptr;
    int64_t* allocation_ = nullptr;
};

// Constructors and memory management
Matrix::Matrix(size_t nrows, size_t ncols) : nrows_(nrows), ncols_(ncols) {
    if (ncols == 0 || nrows == 0 || (nrows * ncols) / ncols != nrows) {
        throw std::runtime_error("Invalid matrix dimensions");
    }
    reallocate();
}

inline Matrix& Matrix::operator=(const Matrix& other) {
    if (nrows_ != other.nrows_ || ncols_ != other.ncols_) {
        nrows_ = other.nrows_;
        ncols_ = other.ncols_;
        reallocate();
    }
    if (other.allocation_) {
        memcpy(allocation_, other.allocation_, sizeof(int64_t) * total_elements());
    } else {
        // for slices, need to copy the rows one by one
        for (size_t i = 0; i < nrows_; ++i) {
            memcpy(data_[i], other.data_[i], sizeof(int64_t) * other.ncols_);
        }
    }
    return *this;
}

inline Matrix& Matrix::operator=(Matrix&& other) {
    memcpy(this, &other, sizeof(Matrix));
    other.data_ = nullptr;
    other.allocation_ = nullptr;
    return *this;
}

inline Matrix Matrix::slice(size_t y1, size_t y2, size_t x1, size_t x2) const {
    y1 = std::min(y1, nrows_);
    y2 = std::min(y2, nrows_);
    x1 = std::min(x1, ncols_);
    x2 = std::min(x2, ncols_);

    Matrix m(y2 - y1, x2 - x1);
    for (size_t i = y1; i < y2; ++i) {
        memcpy(m.data_[i - y1], data_[i] + x1, sizeof(int64_t) * (x2 - x1));
    }

    return m;
}


inline void Matrix::reallocate() {
    delete[] allocation_;
    delete[] data_;

    allocation_ = new int64_t[nrows_ * ncols_];
    data_ = new int64_t*[nrows_];
    if (!allocation_ || !data_) {
        delete[] allocation_;
        delete[] data_;
        throw std::runtime_error("Unable to allocate matrix");
    }

    memset(allocation_, 0, sizeof(int64_t) * nrows_ * ncols_);
    for (size_t i = 0; i < nrows_; ++i) {
        data_[i] = allocation_ + (ncols_ * i);
    }
}

// Artihmetic ops of the form: int op matrix
#define int_matrix_arithmetic_operation_new_copy(op)            \
    inline Matrix operator op(int64_t n, const Matrix& m) {     \
        Matrix res(m.nrows(), m.ncols());                       \
        for (size_t i = 0; i < m.nrows(); ++i) {                \
            for (size_t j = 0; j < m.ncols(); ++j) {            \
                res[i][j] = n op m[i][j];                       \
            }                                                   \
        }                                                       \
        return res;                                             \
    }


int_matrix_arithmetic_operation_new_copy(+);
int_matrix_arithmetic_operation_new_copy(-);
int_matrix_arithmetic_operation_new_copy(*);
int_matrix_arithmetic_operation_new_copy(/);
int_matrix_arithmetic_operation_new_copy(%);


// Matrix Multiplication
inline Matrix Matrix::mm(const Matrix& other) const {
    if (ncols_ != other.nrows_) {
        fprintf(stderr, "%zu %zu | %zu %zu\n", nrows_, ncols_, other.nrows_, other.ncols_);

        throw std::runtime_error("Matrix shapes do not align");
    }

    Matrix res(nrows_, other.ncols_);
    if (ncols_ == nrows_ && other.nrows_ == other.ncols_) {
        // For now, only do strassen for square matrices
        return mm_strassen(res, *this, other);
    }
    return mm_naive(res, *this, other);
}

Matrix Matrix::mm_naive(Matrix& res, const Matrix& a, const Matrix& b) {
    #define LOOP()                                                  \
        for (size_t j = 0; j < b.ncols(); ++j) {                    \
            int64_t b_col[b.nrows()];                               \
            for (size_t n = 0; n < b.nrows(); ++n) {                \
                b_col[n] = b[n][j];                                 \
            }                                                       \
                                                                    \
            for (size_t i = 0; i < a.nrows(); ++i) {                \
                for (size_t k = 0; k < a.ncols(); ++k) {            \
                    res[i][j] += a[i][k] * b_col[k];                \
                }                                                   \
            }                                                       \
        }

    if (b.ncols() < 256) {
        LOOP();
    } else {
        #pragma omp parallel for
        LOOP();
    }

    return res;
}

Matrix Matrix::mm_strassen(Matrix& res, const Matrix& a, const Matrix& b) {
    if (a.nrows() % 2 != 0 || a.nrows() < STRASSEN_CUTOFF) {
        // Just don't bother with the odd case... for now
        return mm_naive(res, a, b);
    }

    size_t n = a.nrows();
    size_t n2 = (n + 1) / 2;

    Matrix a11 = a.slice(0, n2, 0, n2);
    Matrix a12 = a.slice(0, n2, n2, n);
    Matrix a21 = a.slice(n2, n, 0, n2);
    Matrix a22 = a.slice(n2, n, n2, n);


    Matrix b11 = b.slice(0, n2, 0, n2);
    Matrix b12 = b.slice(0, n2, n2, n);
    Matrix b21 = b.slice(n2, n, 0, n2);
    Matrix b22 = b.slice(n2, n, n2, n);


    Matrix m1, m2, m3, m4, m5, m6, m7;
    #pragma omp parallel sections
    {
        #pragma omp section
        m1 = (a11 + a22).mm(b11 + b22);

        #pragma omp section
        m2 = (a21 + a22).mm(b11);

        #pragma omp section
        m3 = a11.mm(b12 - b22);

        #pragma omp section
        m4 = a22.mm(b21 - b11);

        #pragma omp section
        m5 = (a11 + a12).mm(b22);

        #pragma omp section
        m6 = (a21 - a11).mm(b11 + b12);

        #pragma omp section
        m7 = (a12 - a22).mm(b21 + b22);
    }

    Matrix c11 = (m1 + m4).sub(m5).add(m7);
    Matrix c12 = m3 + m5;
    Matrix c21 = m2 + m4;
    Matrix c22 = (m1 - m2).add(m3).add(m6);


    for (size_t i = 0; i < n2; ++i) {
        for (size_t j = 0; j < n2; ++j) {
            res[i][j] = c11[i][j];
        }
        for (size_t j = n2; j < n; ++j) {
            res[i][j] = c12[i][j - n2];
        }
    }

    for (size_t i = n2; i < n; ++i) {
        for (size_t j = 0; j < n2; ++j) {
            res[i][j] = c21[i - n2][j];
        }
        for (size_t j = n2; j < n; ++j) {
            res[i][j] = c22[i - n2][j - n2];
        }
    }

    return res;
}


std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << m.to_string();
    return os;
}

std::string Matrix::to_string() const {
    std::string res = "[";
    for (size_t i = 0; i < nrows_; ++i) {
        res += " [";
        for (size_t j = 0; j < ncols_; ++j) {
            res += std::to_string(data_[i][j]);
            if (j != ncols_ - 1) {
                res += ", ";
            }
        }

        res += "],";
        if (i != ncols_ - 1) {
            res += "\n";
        }
    }
    res += "]";
    return res;
}
