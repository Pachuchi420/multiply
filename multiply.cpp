#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>


std::vector<int> inputVector(){ 
    std::string numStr;
    std::vector<int> num;

    std::cout << "Enter a number: ";
    std::cin >> numStr;

    for(char c : numStr) {
        if(isdigit(c)) {
            num.push_back(c - '0');
        } else {
            std::cout << "Non-digit character encountered. Exiting." << std::endl;
            exit(1);
        }
    }
    return num;
}

void printVector(const std::vector<int>& vec, const std::string& name ){
    std::cout << name << " is: [";
    for(int n : vec){
        std::cout << n << " ";
    }
    std::cout << "\b]" << std::endl;
}

void printMatrix(const std::vector<std::vector<int>>& matrix){ 
    std::cout << "\nThe matrix: " << std::endl;
    for (int i = 0; i < matrix.size(); i++){
        printVector(matrix[i], "line" + std::to_string(i));
    }
    std::cout << std::endl;
}

int convertVector(const std::vector<int>& vector){

    int result = 0; 
    for (int digit : vector){
        result = result * 10 + digit;
    }
    return result;
}

std::vector<int> finalAddition(const std::vector<std::vector<int>>& matrix) {
    int numberOfRows = matrix.size();
    int numberOfColumns = matrix[0].size();

    std::vector<int> result(numberOfColumns);
    int carry = 0;

    for (int col = numberOfColumns - 1; col >= 0; col--) {
        int colSum = 0;
        for (int row = 0; row < numberOfRows; row++) {
            colSum += matrix[row][col];
        }

        colSum += carry;

        result[col] = colSum % 10;
        carry = colSum / 10;
    }

    // If there's any residual carry, prepend it to the result vector
    while (carry) {
        result.insert(result.begin(), carry % 10);
        carry /= 10;
    }

    return result;
}

std::vector<int> multiplyNum(std::vector<int> a, std::vector<int> b){

    // Sizes of vectors
    int sizeA = a.size();
    int sizeB = b.size(); 
    int indexA = sizeA - 1; 
    int indexB = sizeB - 1; 
    int resultingSize = sizeA + sizeB + 1;

    
    // Creating vector with enough space for result
    std::vector<int> result(resultingSize);

    // Create matrix
    std::vector<std::vector<int>> matrix(sizeA, std::vector<int>(resultingSize));
    printMatrix(matrix);

    // Column for each row
    int column = resultingSize - 1; 
    std::cout <<"Column number: "<< column << std::endl;

    int columnStart = resultingSize - 1; 

    for(int aDigits = indexA, rowNumber = 0; aDigits >= 0; aDigits--, rowNumber++){
            int product = a[aDigits] * b[sizeB - 1]; 
            int left = product / 10; 
            int right = product % 10;

            int currentColumn = columnStart - rowNumber;

            matrix[rowNumber][currentColumn] = right;
            currentColumn--;
            
            
            for(int bDigits = indexB - 1; bDigits >= 0; bDigits--){
                product = a[aDigits] * b[bDigits] + left;
                left = product / 10; 
                right = product % 10;
                matrix[rowNumber][currentColumn] = right;
                currentColumn--;
            }

            matrix[rowNumber][currentColumn] = left; 
    }
    printMatrix(matrix);
    std::vector<int> finalResult = finalAddition(matrix);
    std::cout << "Final result: " << convertVector(finalResult) << std::endl;

    return(finalResult);
    
}

int main(){
    std::vector<int> a = inputVector();
    std::vector<int> b = inputVector();
    multiplyNum(b, a);
}