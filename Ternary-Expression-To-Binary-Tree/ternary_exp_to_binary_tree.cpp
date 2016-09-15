#include<iostream>
#include <vector>
#include <stack>

/* 
  This program converts a ternary expression into a Binary Tree
*/


class Node{
public:
  Node(char ch): data(ch), right(NULL), left(NULL) { }
  char data;
  Node* right;
  Node* left;
//  Node* parent;  
};


/* Method to get the original ternary expression order from the Binary tree*/
void getPreOrder(Node* root, std::vector<char>& vec){
  if(root == NULL)
    return ;
  vec.push_back(root->data);
  vec.push_back('?');
  getPreOrder(root->left, vec);
  vec.push_back(':');
  getPreOrder(root->right, vec);
}


/*
  Put the first char at the root.
  If the next char is ?, put the char following it to the left of the current node and make this the current node.
  If the next char is :, make the current node's parent the current node and until either the current node's parent and it's right node is NULL, keep moving the current node upwards.
  Put the char following : to the right of the current node and make this the current node.
*/

Node* ternaryToBinaryTree(std::vector<char> vec){
  Node* root = new Node(vec[0]);
  std::stack<Node*> st;
  st.push(root);
  
  int i = 0;
  while(++i < vec.size()){
    if(vec[i] == '?'){
      st.top()->left = new Node(vec[i+1]);
      st.push(st.top()->left);
    }else if(vec[i] == ':'){
      st.pop();
      while(st.top()->right != NULL && ! st.empty() ){ 
        st.pop();
      }
      st.top()->right = new Node(vec[i+1]);
      st.push(st.top()->right);
    }
   ++i;
  }
  return root;
}

/*  Method to print the ternary expression */
void printTernary(std::vector<char> vec){
  for(int i=0; i < vec.size() - 1; ++i){
    if(vec[i] == '?' || vec[i] == ':'){
      while( (vec[i+1] == '?' || vec[i+1] == ':') ){
        ++i;
        if(i >= vec.size() - 1) break;
      }
      if(i < vec.size() - 1)
        std::cout << vec[i] << " ";
    }else{
      std::cout << vec[i] << " ";
    }
  }
}

int main(){
  std::vector<char> vec{'a','?','b','?','c', ':', 'd','?','e',':', 'f', ':', 'g'};
  std::vector<char> vec2;
  getPreOrder(ternaryToBinaryTree(vec), vec2);
  printTernary(vec2);
  std::cout << "" << std::endl;
}
