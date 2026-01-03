#pragma once

#include <unordered_map>
#include <utility>
#include <cstddef>

template<typename T, T defaultValue>
class Matrix {
   
public:
    using KeyType = std::pair<std::size_t, std::size_t>;

    class CellProxy{
    private:
        Matrix& matrix_;
        std::size_t row_;
        std::size_t col_;

    public:
        CellProxy(Matrix& m, std::size_t r, std::size_t c) : matrix_(m), row_(r), col_(c) {}

        CellProxy& operator=(const T& value) {
            KeyType key{row_, col_};

            if(value == defaultValue) {
                matrix_.data_.erase(key);
            }else {
                matrix_.data_[key] = value;
            }

            return *this;
        }

        operator T() const {
            auto it = matrix_.data_.find({row_, col_});
            return (it == matrix_.data_.end()) ? defaultValue : it->second;
        }

    };

    class RowProxy {
    public:
        RowProxy(Matrix& m, std::size_t r) : matrix_(m), row_(r){}

        CellProxy operator[](std::size_t col) {
            return CellProxy(matrix_, row_, col);
        }
    
    private:
        Matrix& matrix_;
        std::size_t row_;
    };
      

    RowProxy operator[](std::size_t row) {
        return RowProxy(*this, row);
    }

    std::size_t size() const {
        return data_.size();
    }

    auto begin() const {return data_.begin();}

    auto end() const {return data_.end();}

private: 

    struct PairHash {
        std::size_t operator()(const KeyType& p) const noexcept {
            return std::hash<std::size_t>{}(p.first) ^ (std::hash<std::size_t>{}(p.second) << 1);
        }
    };
    std::unordered_map<KeyType, T, PairHash> data_;

};