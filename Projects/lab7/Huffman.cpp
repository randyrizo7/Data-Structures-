#include "Huffman.h"

bool HuffmanTree::createCodeTree(string filename) {
    std::priority_queue<
            BST<CharFreq>::BSTNode*,
            std::vector<BST<CharFreq>::BSTNode*>,
            BST<CharFreq>::FrequencyCompare
    > myPriorityQ;
    string str;
    string allText = "";
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        cout << "ERROR loading file!\n";
        return false;
    }
    while (!infile.eof()) {    // To get you all the lines.
        getline(infile,str); // Saves the line in STRING.
        allText += str + "\n";
    }
    infile.close();

    // **************************************************************
    // TODO: createCodeTree - add code here
    //  1. Count occurrences of every letter or symbol that you care about in
    //     allText (consider spaces ' ', newlines '\n', periods, commas,
    //     question marks, quotation marks, etc.
    //  2. Use myPriorityQ to build a tree, as described in the assignment.
    //  3. Set root (inherited from BST) to the final item in myPriorityQ
    //     (in other words, when there is a single tree in myPriorityQ).


    // denote each character and its frequency
    // create const variable
    int const SIZE = 128;

    // create int array
    int freq[SIZE] = {0};

    // loop through each character

    // populate freq array
    for(char c : allText) {
        freq[(int) c]++;
    }
    // assign character and its frequents to new created Node
    for (unsigned t = 0; t < SIZE; t++){
        if(freq[t] > 0) {
            BST<CharFreq>::BSTNode* treeNode = new BST<CharFreq>::
            BSTNode(CharFreq((char)t, freq[t]));
            myPriorityQ.push(treeNode);
        }
    }

    // crceate node pointer to point to node on heap

    while(myPriorityQ.size() > 1) {
        BST<CharFreq>::BSTNode* left = myPriorityQ.top();
        myPriorityQ.pop();

        BST<CharFreq>::BSTNode* right = myPriorityQ.top();
        myPriorityQ.pop();

        float freqSum = left->data.frequency + right->data.frequency;

        BST<CharFreq>::BSTNode* newNode = new BST<CharFreq>::
        BSTNode(left,right,CharFreq('\0', freqSum));

        myPriorityQ.push(newNode);
    }

    root = myPriorityQ.top();
    // **************************************************************

    return true;
}

bool HuffmanTree::encodeFile(string originalFilename, string outputFilename) {
    string str;
    string allText = "", currentStream = "";
    ifstream infile;
    const int WRITE_SIZE = 8;

    infile.open(originalFilename.c_str());
    if( !infile.is_open() ) {
        cout << "ERROR loading file!\n";
        return false;
    }
    while (!infile.eof()) {        // To get you all the lines.
        getline(infile, str);   // Saves the line in string.
        allText += str + "\n";
    }
    infile.close();

    std::ofstream outStream(outputFilename.c_str(), std::ios::binary);
    if (!outStream.is_open()) {
        cout << "ERROR creating output file!\n";
        return false;
    }

    for (int i = 0; i < (int)allText.length(); i++) {
        // **************************************************************
        // TODO: encodeFile - add your code here
        //  add the appropriate encoding for allText[i] to currentStream
        // currentStream += ""; // may need to update this line

        // initiate vector
        vector<int> encodeString;

        // call helper function
        helper(root, allText[i], encodeString);

        // for loop for encoding
        for (int k : encodeString){
            if (k)
                currentStream += '1';
            else
                currentStream += '0';
        }
        // **************************************************************

        while ((int)currentStream.length() > WRITE_SIZE) {
            string byte = currentStream.substr(0, WRITE_SIZE);
            bitset<8> set(byte);
            const char toWrite = (unsigned char)((unsigned int)set.to_ulong());
            outStream.write(&toWrite,sizeof(char));
            currentStream = currentStream.substr
                    (WRITE_SIZE,currentStream.length() - WRITE_SIZE);
        }
    }

    outStream.close();
    return false;
}


// helper function
bool HuffmanTree::helper(BST<CharFreq>::BSTNode* ptr, char character,
                         vector<int> &encodeString){
    if (ptr == nullptr)
        return false;

    if (ptr->data.letter == character)
        return true;


    if (ptr->left){
        encodeString.push_back(0);
        if (helper(ptr->left, character, encodeString))
            return true;
        encodeString.pop_back();
    }

    if (ptr->right){
        encodeString.push_back(1);
        if (helper(ptr->right, character, encodeString))
            return true;
        encodeString.pop_back();
    }

    return false;
}

bool HuffmanTree::decodeFile(string filename) {
    int i = 0; string bitStream = "";
    ifstream encodedfile;

    encodedfile.open(filename.c_str(), ios::binary);
    if (!encodedfile.is_open()) {
        cout << "ERROR opening encoded file!\n";
        return false;
    }

    encodedfile >> std::noskipws;
    while (!encodedfile.eof()) {
        unsigned char readMe;
        encodedfile >> readMe;
        bitset<8> set((unsigned long)readMe);
        bitStream += set.to_string();
    }

    encodedfile.close();

    while (i != -1)
        i = traverseAndPrint(bitStream, i);
    return false;
}

int HuffmanTree::traverseAndPrint(string &bits, int i, BSTNode *cur) {
    if(i >= (int)bits.length())
        return -1;
    // **************************************************************
    // TODO: traverseAndPrint - add your code here
    //  Write this function using recursion. This is essentially your decode
    //  function.  You need to step through the tree based on reading 0 or 1
    //  and when you reach a leaf, print (using cout) the appropriate character.
    //  - i represents your current location in the string
    //  - cur represents the cur node in your tree
    //  Don't forget that you need to keep going after printing out a character
    //  (which means restarting at the top of the tree)

    // print out characters using recursion
    if (cur->left == nullptr && cur->right == nullptr) {
        cout << cur->data.letter;
        return traverseAndPrint(bits, i, root);
    }
    if (bits[i] == '0'){
        return traverseAndPrint(bits, i + 1, cur->left);
    }
    if (bits[i] == '1'){
        return traverseAndPrint(bits, i + 1, cur->right);
    }
    // **************************************************************

    return -1;
}

void HuffmanTree::helper2(ostream &out, BSTNode *ptr, vector<int>
&encodeString) {
    if (root == nullptr)
        return;

    if (ptr->left == nullptr && ptr->right == nullptr) {
        out << ptr->data.letter << " : ";

        for(int i : encodeString) {
            out << i;
        }
        out << endl;
    }

    if (ptr->left){
        encodeString.push_back(0);
        helper2(out, ptr->left, encodeString);
        encodeString.pop_back();
    }

    if (ptr->right){
        encodeString.push_back(1);
        helper2(out, ptr->right, encodeString);
        encodeString.pop_back();
    }
}


void HuffmanTree::displayCode(ostream &out) {
    // **************************************************************
    // TODO: displayCode - add your code here
    //  Print out each letter and its code, you might want to check for
    //  special cases (space, newline, etc.)

    vector<int> encodeString;

    // call helper2 function
    helper2(out, root, encodeString);

    // **************************************************************
}


ostream& operator<<(ostream &out, HuffmanTree &code) {
    code.displayCode(out);
    return out;
}