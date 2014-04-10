#include "stdafx.h"
#include "Problems.h"
#include "iostream"
#include <vector>
#include <map>
#include <queue>

using namespace std;

void GetAndPrintEvenOdd()
{
    int maxOdd = INT_MIN;
    int minEven = INT_MAX;
    int input = 0;
    bool firstTime = true;

    while (cin >> input)
    {
        if (input == 0)
            break;

        // Is even
        if (input % 2 == 0)
        {
            if (input < minEven)
                minEven = input;
        }
        else if (input > maxOdd)
        {
            maxOdd = input;
        }
        if (firstTime)
        {
            cout << "Input no is " << endl;
            firstTime = false;
        }
        cout << input << ", ";
    }

    if (maxOdd != -1)
        cout << "Max odd is " << maxOdd << endl;

    if (minEven != -1)
        cout << "MIn Even is " << minEven << endl;
}


void ReturnTheChange()
{
#define DENOMINATIONS 13
    // currency in cents
    int currencyDenomination[DENOMINATIONS] = {100000, 50000, 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
    int denoCount[DENOMINATIONS] = {0};
    float number;

    cin >> number;

    int input = (int)(number * 100);
    int denoIndex = 0;

    for (int remainder = input; remainder >= 5; )
    {
        while (remainder > currencyDenomination[denoIndex])
        {
            denoCount[denoIndex]++;
            remainder -= currencyDenomination[denoIndex];
        }
        denoIndex++;
    }
    float change = 0;

    for(int i = 0; i < DENOMINATIONS; ++i)
    {
        if (denoCount[i] > 0)
        {
            change += denoCount[i] * (float)currencyDenomination[i]/100;
            cout << " Need " << denoCount[i] << ", " << (float)currencyDenomination[i]/100 << "  denomination" << endl;
        }
    }

    cout << "\nTotal change is " << change << endl;

    if (number - change > 0)
        cout << number - change << "cents rounded off" << endl;

    getchar();
}


class Node
{
public:
    Node(char ch, int key);
    ~Node();

    Node *next;
    char data;
    int key;
};

Node::Node(char ch, int keyNo) : next(NULL), data(ch), key(keyNo)
{
}

Node::~Node()
{
}

class LocalAutomaton
{
public:
    LocalAutomaton()
    {
        BuildAutomaton();
    }
    vector<char>GetTheKeyowrd(char *numberStr);

protected:
    void BuildAutomaton();
    void Traverse(Node *currentNode, char *&numberStr, vector<char>& name);

private:
    Node *BuildNodes(char startChar, int key, int keyNums);
private:
    vector<Node *> mList;
};

void LocalAutomaton::BuildAutomaton()
{
    mList.push_back(BuildNodes(' ', 0, 0));
    mList.push_back(BuildNodes(' ', 1, 0));
    mList.push_back(BuildNodes('A', 2, 3));
    mList.push_back(BuildNodes('D', 3, 3));
    mList.push_back(BuildNodes('G', 4, 3));
    mList.push_back(BuildNodes('J', 5, 3));
    mList.push_back(BuildNodes('M', 6, 3));
    mList.push_back(BuildNodes('P', 7, 3));
    mList.push_back(BuildNodes('S', 8, 3));
    mList.push_back(BuildNodes('V', 9, 4));
}

 Node *LocalAutomaton::BuildNodes(char startChar, int key, int keyNums)
 {
     Node *primaryNode = new Node(startChar, key);
     Node *intermediateNode = primaryNode; 
     Node *newNode = NULL;

     --keyNums;

     for (int i = 0; i < keyNums; ++i)
     {
         newNode = new Node(++startChar, key);
         intermediateNode->next = newNode;
         intermediateNode = newNode;
     }
     intermediateNode->next = primaryNode;

     return primaryNode;
 }

 vector<char>LocalAutomaton::GetTheKeyowrd(char *numberStr)
 {
     vector<char> keyword;
     size_t length = strlen(numberStr);
     Node *initNode = mList[*numberStr - '0'];
     Node *intermediate = NULL;

     //for(int i =0; i < length; ++i)
     while (*numberStr != NULL)
     {
         Node *initNode = mList[*numberStr - '0'];
         Traverse(initNode, numberStr, keyword);
     }

     return keyword;
 }
 
 void LocalAutomaton::Traverse(Node *currentNode, char *&numberStr, vector<char>& name)
 {
     Node *intermediate = currentNode;

     while (intermediate && numberStr)
     {
         char ch = *(++numberStr);

         if (intermediate->next != NULL && intermediate->next->key == ch - '0')
         {
             intermediate = intermediate->next;
         }
         else
         {
             name.push_back(intermediate->data);
             break;
         }
     }
 }


void PrintNumberToKeyword()
{
    char *numStr = new char[100];

    cin >> numStr;

    LocalAutomaton automaton;
    vector <char> keyword = automaton.GetTheKeyowrd(numStr);

    for each (char var in keyword)
    {
        if (var != ' ')
            cout << var ;
    }

    delete []numStr;
}

void PrintDate()
{
#define MONTHS 12
    int daysInMonth[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year;
    cin  >> year;

    if ((year % 400 == 0) || ((year % 4 == 0) && (year %100 != 0)))
    {
        daysInMonth[1] = 29;
    }

    for (int month = 0; month < MONTHS; ++month)
    {
        for (int day = 0; day < daysInMonth[month]; ++day)
        {
            cout << day + 1 << ", " << month + 1 << "," << year << endl;
        }
        cout << "End of month \n\n";
    }

}

void SpiralTraversal()
{
#define ROWS 5
#define COLS 5
    int matrix[ROWS][COLS];
    int number = 1;

    for(int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            matrix[i][j] = ++number;
        }
    }

    for(int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            cout << matrix[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;

    int startRow = 0;
    int endRow = ROWS;
    int startCol = 0;
    int endCol = COLS;

    {
        int rowIndex = 0; 
        int colIndex = 0;
        int incr = 1;

        while (startRow <= endRow && startCol <= endCol)
        {
            rowIndex = startRow;
            colIndex = startCol;

            while(rowIndex >= startRow && rowIndex < endRow)
            {
                cout << matrix[colIndex][rowIndex] << ",";
                rowIndex += incr;
            }
            --rowIndex;
            ++startCol;

            colIndex = startCol;
            while(colIndex >= startCol && colIndex < endCol)
            {
                cout << matrix[colIndex][rowIndex] << ",";
                colIndex += incr;
            }
            --colIndex;
            --endRow;

            incr *= -1;

            rowIndex = endRow - 1;
            while(rowIndex >= startRow && rowIndex < endRow)
            {
                cout << matrix[colIndex][rowIndex] << ",";
                rowIndex += incr;
            }
            ++rowIndex;
            --endCol;

            colIndex = endCol - 1;
            while(colIndex >= startCol && colIndex < endCol)
            {
                cout << matrix[colIndex][rowIndex] << ",";
                colIndex += incr;
            }
            ++startRow;
        }
    }
}
//
//0 - NULL 
//1 - v, t, f, r, q 
//2 - f, t, k 
//3 - w, z, b, g 
//4 - r, s 
//5 - NULL 
//6 - f, i, r 
//7 - p 
//8 - l, o 
//9 - p 

void Combination(string prefix, char* num)
{
    static string str[] = {"","vtfrq","ftk","wzbg","rs","","fir","p","lo","p"};

    if (*num == NULL)
    {
        cout << prefix.c_str() << ",";
    }
    else
    {
        int number = *num - '0';
        string temp = str[number];

        if (temp.length() !=0 )
        {
            for(int i = 0; i < temp.length(); ++i)
            {
                Combination(prefix+temp.at(i), ++num);
                --num;
            }
        }
        else
        {
            Combination(prefix, ++num);
            --num;
        }
    }
}

void PrintNumberToAllPossibleKeyword()
{
    char inputStr[100];

    cin >> (char*)inputStr;

    Combination("", inputStr);
}

bool PrintOrderedNumber(int num, int prevNum, int maxNum, int numOfDigit)
{
    bool haltGen = false;

    if (numOfDigit == 0)
    {
        cout << num << endl;

        if (num >= maxNum)
            haltGen = true;
    }
    else
    {
        for(int i = prevNum + 1; i < 10 && !haltGen; ++i)
        {
            haltGen = PrintOrderedNumber(num * 10 + i, i, maxNum, numOfDigit - 1);
        }
    }

    return haltGen;
}

void PrintOrderedNumber()
{
    int numOfDigit;
    cin >> numOfDigit;
    int startNumber;
    int endNumber;
    cout << "Enter start and end range";

    cin >> startNumber;
    cin >> endNumber;

    int startNum = startNumber/(pow(10, numOfDigit - 1) - 1);

    PrintOrderedNumber(0, startNum - 1, endNumber, numOfDigit);
}

vector<pair <int, int>>::iterator Find(vector<pair <int, int>> &looker, int num)
{
    vector<pair <int, int>>::iterator iter = looker.begin();

    for (; iter != looker.end(); ++iter)
    {
        if ((*iter).first == num)
            return iter;
    }

    return looker.end();
}

void ReadList(vector<int> &listOfNo, vector<pair <int, int>> &looker)
{
    int prevNo = -1;
    int count = 0;
    vector<int>::iterator iter = listOfNo.begin();

    while (iter != listOfNo.end())
    {
        prevNo = (*iter);
        ++iter;
        count = 1;
        while (iter != listOfNo.end() && (*iter) == prevNo)
        {
            ++count;
            ++iter;
        }

        looker.push_back(pair<int, int>(prevNo, count));
    }
}

void LookAndSay()
{
    int noOfIteration = 10;
    cin >> noOfIteration;
    vector<int> listOfNo;
    listOfNo.push_back(1);

    for (int iter = 0; iter < noOfIteration; ++iter)
    {
        vector<pair <int, int>> looker;
        ReadList(listOfNo, looker);
        listOfNo.clear();
        for each (pair<int, int> var in looker)
        {
            listOfNo.push_back(var.second);
            listOfNo.push_back(var.first);
        }

        for each (int var in listOfNo)
        {
            cout << var;
        }
        cout << endl;
    }
}

/* Magic board

    8, 1, 6
    3, 5, 7
    4, 9, 2

    For any winning move the sum of occupied cells by a player should be 15
*/
class TicTakToeGame
{
private:
     static bool board[10]; //the tic-tac-toe board
     string name;   //the name of the specific player
     bool trying;  //false if this player has won
     bool taken[10]; //indicates squares occupied by this player
     bool pairs[16]; //array marks two in a row for this player
    static TicTakToeGame player; //the players

public:
    string getName() {
        return name;
    }//getName
    bool isTaken(int spot) {
        return taken[spot];
    }
    bool isTrying() { //player stops trying after winning
        return trying;
    }//isTrying
    void setName(string playerName)
    {
        name = playerName;
    }
    TicTakToeGame() { //constructor
        //taken  = new bool[10];
        //pairs  = new bool[16];
        for (int i = 0; i < 10; ++i)
        {
            taken[i] = false;
        }

        for (int i = 0; i < 16; ++i)
        {
            pairs[i] = false;
        }

        trying  = true;
    }//constructor

    // game playing strategy goes here - this version makes random moves
    void move() { //make a random move
        int spot;
        do {     //find an empty board location
            spot = (int)(rand() % 9 + 1);
        } while (board[spot]);
        //System.out.println(name + ": move to " + spot);

        if (pairs[15-spot]) {//check for a win
            //System.out.println(name + "WIN");
            trying = false;
            taken[spot] = true;
        } else {
            for (int j=1; j<10; j++) { //update pairs array
                if (taken[j] && j + spot < 15) {
                    pairs[j+spot] = true;
                    //System.out.println(">>>>>>> " + name + " setting " + (j+spot));
                }//if
            }//for j
        }//else
        taken[spot] = board[spot] = true;
    }//move
}; //classREFERENCES

bool TicTakToeGame::board[];

void TikTacToe()
{
    TicTakToeGame player[2];
    player[0].setName("Sam");
    player[1].setName("Pat");
    int who = 1; //player numbers are 1 and 0

    for (int k=0; k<9 && player[0].isTrying() && player[1].isTrying(); k++) {
            player[who].move();
            //printBoard();
            who = 1 - who; //now it’s the other player’s turn
    } //for
}//main

void SquareRoot(float number)
{
    float result = 1.0;
    float prevResult = 0.0;

    while (fabs(result-prevResult) > 0.001)
    {
        prevResult = result;
        result = (prevResult + number/prevResult)/2;
    }

    cout << result;
}

bool IsReplacingChar(const char *str, int index, char replacingChar)
{
    return (tolower(str[index]) == 'a' && (str[index - 1] == ' ' || index == 0) && (str[index + 1] == ' ' || str[index + 1] == '\0'));
}

void ReplaceCharWithString(const char *str, char replacingChar, char *replacementStr)
{
    char *newStr = new char[strlen(str) * strlen(replacementStr) + 1];
    int index = 0;
    int newIndex = 0;

    cout << str << endl;

    while (str[index] != '\0')
    {
        if (IsReplacingChar(str, index, replacingChar))
        {
            int i = 0;

            while(replacementStr[i] != '\0')
            {
                newStr[newIndex++] = replacementStr[i++];
            }
            ++index;
        }
        else
        {
            newStr[newIndex] = str[index];
            ++index;
            ++newIndex;
        }
    }

    newStr[newIndex] = '\0';

    cout << newStr << endl<<endl;

    delete [] newStr;
}

class GreaterThan
{
public :
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

void PushNumToList(int ignoreNums[], int input)
{
    int size = 3;//sizeof(ignoreNums)/sizeof(int);
    int i = 0;

    while (i < size && ignoreNums[i] > input)
        ++i;

    if (i < size)
    {
        int insertIndex = i;
        // move 
        
        while (--size > i)
        {
            ignoreNums[size] = ignoreNums[size - 1];
            
        }

        ignoreNums[insertIndex] = input;
    }
}

void IgnoreNLargestInMean()
{
    int ignoreNums[3] = {-999};
    priority_queue<int, vector<int>, GreaterThan> largetNumList;
    int sum = 0;
    int noOfItems = 0;
    int input = 0;
    cin >> input;

    while (input != -999)
    {
        PushNumToList(ignoreNums, input);
        sum += input;
        ++noOfItems;
        cin >> input;
    }

    for each (int var in ignoreNums)
    {
        sum -= var;
    }

    cout << "Mean is " << sum/noOfItems;
}

void SubsetSum()
{
    int a[] = {1, 7, 6, 3, 5, 8, 9, 0};
    int sum[8][8] = {0};

    for (int i = 0; i < 7; ++i)
    {
        sum[i+1][i+1] = a[i];
    }

    for (int i = 1; i < 8; ++i)
    {
        for (int j = 1; j < 8; ++j)
        {
            cout << sum[i][j] <<"\t,";
        }
        cout << endl;
    }

    for (int i = 1; i < 8; ++i)
    {
        for (int j = i; j < 8; ++j)
        {
            sum[i][j] += a[j] + sum[i][j-1];
        }
    }
     

    cout << "Solution matrix \n";

    for (int i = 1; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            cout << sum[i][j] <<"\t,";
        }
        cout << endl;
    }

}

const int m = 4;
const int n=4;
int static original[m][n] = {{2, 3, 4, 5},
{4, 5, 10, 11 },
{20, 6, 9, 12 },
{6, 7, 8, 40 }};
int static longest[m][n] = {0};
int findfor(int i, int j);
int findLSI() {
    int max = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int current = findfor(i, j);
            if (current > max) { max = current; }
        }
    }
    return max;
}

int findfor(int i, int j) {
    if (longest[i][j] == 0) {
        int max = 0;
        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                if (!(k == 0 && l == 0) && i + k >= 0 && i + k < m && j + l >= 0
                    && j + l < n && original[i + k][j + l] > original[i][j])
                {
                    int current = findfor(i + k, j + l);
                    if (current > max) { max = current; }
                }
            }
        }
        longest[i][j] = max + 1;
    }
    return longest[i][j];
}

void PrintOneMissingKey()
{
    int origSeq[] = {1, 2, 6, 4, 6};

    for each (int missingKey in origSeq)
    {
        for each(int num in origSeq)
        {
            if (num != missingKey)
            {
                cout << num << ",";
            }
        }
        cout <<endl;
    }
}

bool CompareWithMissingKey(const char *origSeq, const char *enteredSeq, char ignorableChar)
{
    while((*origSeq) != '\0' && (*enteredSeq) != '\0')
    {
        // Skip sequence of ignorable Char
        while((*origSeq) != '\0' && (*origSeq) == ignorableChar) { origSeq++;}

        if ((*origSeq) == '\0')
            break;

        if ((*origSeq) != (*enteredSeq))
            return false;

        ++origSeq;
        ++enteredSeq;
    }

    // Skip any trailing ignorable Char
    while((*origSeq) != '\0' && (*origSeq++) == ignorableChar) { }

    if ((*origSeq) == (*enteredSeq))
        return true;

    return false;
}

void CompareSecurityCodeWithMissingKey()
{
    char *origSeq = "1266466";
    char *enteredSeq[] = {"124", "1266", "6612", "1264", "24", "2646", "126666"};

    cout << "Original Sequence" << origSeq << endl;

    for (int j = 0; j < sizeof(enteredSeq)/sizeof(char*); ++j)
    {
        bool isAcceptable = false;
        for (unsigned int i = 0; i < strlen(origSeq); ++i)
        {
            if (CompareWithMissingKey(origSeq, enteredSeq[j], origSeq[i]))
            {
                cout << enteredSeq[j] << " sequence is acceptable\n";
                isAcceptable = true;
                break;
            }
            
        }
        if (!isAcceptable)
            cout << enteredSeq[j] << " sequence is not acceptable\n";
    }
}

// Return true if both code are same or has JUST one error
// When one error returns realChar and userChar that are different
bool IsCodeComparable(const char* realCode, const char* userCode, char &realChar, char &userChar)
{
    int mismatchCount = 0;

    while((*realCode) != '\0' && (*userCode) != '\0')
    {
        if ((*realCode) != (*userCode))
        {
            ++mismatchCount;

            realChar = *realCode;
            userChar = *userCode;

            if (mismatchCount > 1)
                return false;
        }
        ++realCode;
        ++userCode;
    }

    if ((*realCode) == '\0' && (*userCode) == '\0' && mismatchCount <= 1)
        return true;

    return false;
}

/*
http://www.careercup.com/question?id=84688
There is a security keypad at the entrance of a building. It has 9 numbers 1 - 9 in a 3x3 matrix format. 
1 2 3 
4 5 6 
7 8 9 

The security has decided to allow one digit error for a person but that digit should be horizontal or vertical. 
Example: for 5 the user is allowed to enter 2, 4, 6, 8 or for 4 the user is allowed to enter 1, 5, 7. 

IF the security code to enter is 1478 and if the user enters 1178 he should be allowed. 
*/
void CheckForKeyPad()
{
    char *realCode = "1453";
    char *userCode = "1183";
    char realChar;
    char userChar;
	bool isComparable = false;

    if (IsCodeComparable(realCode, userCode, realChar, userChar))
    {
		int realInt = realChar - '0';
		int userInt = userChar - '0';
        int row = (realInt - 1) / 3;
        int col = (realInt - 1) % 3;
	
        if (userInt >= 3*row+1 && userInt <= 3*row + 3)
		{
			isComparable = true;
		}

		for (int rowNum = 0; rowNum < 3; ++rowNum)
		{
			if (userInt == 3*rowNum+col+1)
			{			
				isComparable = true;
				break;
			}
		}
    }

	if (isComparable)
		cout << "Code is accepted";
	else
		cout << "Code is not accepted";
}