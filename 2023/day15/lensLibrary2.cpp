#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>

struct s_lense{
  std::string label;
  int focal_length;
};

int hash(std::string sequence)
{
  int result = 0;
  for( auto c: sequence){
    result += c;
    result *= 17;
    result %= 256;
  }
  return result;
}

int main(void)
{
    std::ifstream inFile;
    std::string sequenceLine;
    std::string label;
    char operation;
    int focal_length = 0, box;
    std::map<int, std::vector<s_lense>> boxes;
    s_lense lense;

    inFile.open("input.txt");
//    inFile.open("test.txt");
    getline( inFile, sequenceLine );
    std::stringstream sequences(sequenceLine);
    for (std::string sequence; getline(sequences, sequence, ','); ){
//      std::cout << sequence << '\n';
      if (sequence.find('=') != std::string::npos) {
        std::cout << "Adding ";
        label=sequence.substr(0, sequence.find('='));
        std::cout << label;
        focal_length = stoi(sequence.substr(sequence.length()-1,sequence.length())); 
        std::cout << ' ' << focal_length << " in ";
        box = hash(label); 
        std::cout << "Box: " << box << '\n';
        lense.label = label;
        lense.focal_length = focal_length;
        int index = -1;
        for (auto it = boxes[box].begin(); it != boxes[box].end(); ++it){
          if (it->label == label){
            index = it - boxes[box].begin();
            boxes[box].erase(it);
            break;
          }
        }
        if (index == -1){
          std::cout << "pushing back\n";
          boxes[box].push_back(lense);
        }
        else{
          std::cout << "replaceing at " << index << '\n';
          boxes[box].insert(boxes[box].begin() + index, lense);
        }
      }
      else if (sequence.find('-') != std::string::npos){
        std::cout << "deleting ";
        label=sequence.substr(0, sequence.find('-'));
        std::cout << label << '\n';
        box = hash(label);
        for (auto it = boxes[box].begin(); it != boxes[box].end(); ++it){
          if (it->label == label){
            std::cout << "deleted!\n";
            boxes[box].erase(it);
            break;
          }
        }
      }
    }
    std::cout << '\n';
    long long int focusingPower = 0; 
    for (auto [i,b]: boxes){
      std::cout << "Box " << i << '\n';
      int ii = 1;
      for (auto l: b){
        std::cout << ii << ' ' << l.label << ' ' << l.focal_length << '\n';
        focusingPower += (i+1) * ii * l.focal_length;
        ii++;
      }
      std::cout << '\n';
    }
    
    std::cout << "What is the focusing power of the resulting lens configuration? " << '\n';
    std::cout << focusingPower << '\n';
    inFile.close();
}
