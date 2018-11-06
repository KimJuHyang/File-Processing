#include <stdio.h>
#include <iostream>

using namespace std;

struct Node
{
   friend class tree;
   int key;
   Node *left, *right;
};

struct Node* getNode(int key) {
  struct Node* newNode = new Node;
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
};


class tree
{
private:
   void insertBST(Node *&, int key);
   void deleteBST(Node *&, int key);
   void inorder(Node*);

public:
   Node *root;
   tree() : root(NULL) { }

   void inorder();
   void insertBST(int key);
   void deleteBST(int key);
   int noNodes(Node *&node);
   int height(Node *&node);
   int maxNode(Node *&node);
   int minNode(Node *&node);
};

int tree::height(Node *&node) {
  if (node == NULL) {
        return -1;
    }

    int lefth = height(node->left);
    int righth = height(node->right);

    if (lefth > righth) {
        return lefth + 1;
    } else {
        return righth + 1;
    }
}

int tree::minNode(Node *&node) {

  while (node->left != NULL)
     node = node->left;

  return node->key;
}

int tree::maxNode(Node *&node) {

  while (node->right != NULL)
     node = node->right;

  return node->key;
}

int tree::noNodes(Node *&node) {

  unsigned int count = 1;
  if (node->left != NULL) {
    count += noNodes(node->left);
    }
    if (node->right != NULL) {
     count += noNodes(node->right);
    }
 return count;
}

void tree::insertBST(Node *&node, int key)
{
   if (node == NULL)
      node = getNode(key);   //탐색하고 있는 노드가 NULL이면 삽입

   else if (key == node->key) {
     return;
   }
   else if (key > node->key)
      insertBST(node->right, key);   //삽입할 key가 노드의 값보다 크면 오른쪽 탐색

   else if (key < node->key)
      insertBST(node->left, key);   //삽입할 key 노드의 값보다 작으면 왼쪽 탐색
}

void tree::deleteBST(Node *& node, int key)
{

   Node *removal = getNode(0);

   if (key > node->key)
      deleteBST(node->right, key);   //삭제할 key가 노드의 값보다 크면 오른쪽 탐색
   else if (key < node->key)
      deleteBST(node->left, key);   //삭제할 key가 노드의 값보다 작으면 왼쪽 탐색

   else {                          //삭제할 노드를 찾았을때
      if (node->left == NULL && node->right == NULL)  //  leaf node
      {
         delete node;
         node = NULL;
      }

      else if (node->left == NULL)    // right child만 있을 때
      {
         removal = node;
         node = node->right;
         delete removal;
      }
      else if (node->right == NULL)   // left child만 있을 때
      {
         removal = node;
         node = node->left;
         delete removal;
      }
      else {                    //노드의 Child가 두개일 때, 높이로 비교하여 대체값 정하기

              bool flag = 0;
              int lefth = height(node->left)+1;
              int righth = height(node->right)+1;

             if (lefth > righth ) { flag = 1; }   //오른쪽의 높이가 더 클때 - 오른쪽 최소값 대체

             else if (lefth < righth) { flag = 0; }   //왼쪽의 높이가 더 클때 - 왼쪽 최대값 대체

             else {                                   //높이가 같을때 - 노드개수로 판단한다.
               int leftno = noNodes(node->left);
               int rightno = noNodes(node->right);

               if (leftno < rightno) { flag = 1; }  //오른쪽의 개수가 더 많을때 - 오른쪽 최소값 대체
               else { flag = 0; }                  // 왼쪽의 개수가 더 많거나 같을때 - 왼쪽 최대값 대체
             }

             if (flag == 1) {             //오른쪽 subtree의 최소값으로 대체해야할때
               removal = node->right;
               int minVal = minNode(removal);
               deleteBST(root, minVal);
               node->key = minVal;
             }

             else {                     //왼쪽 subtree의 최대값으로 대체해야할때
               removal = node->left;
               int maxVal = maxNode(removal);
               deleteBST(root, maxVal);
               node->key = maxVal;
             }

          }
    }
}

void tree::inorder(Node *node)
{
   if (node != NULL)
   {
      inorder(node->left);
      cout << node->key << " ";
      inorder(node->right);
   }
}

void tree::insertBST(int key) { insertBST(root, key); }
void tree::deleteBST(int key) { deleteBST(root, key); }
void tree::inorder() { inorder(root); cout << endl;}

int main() {
  tree T; tree();
  cout << endl <<  " <<<<<< insertBST >>>>>>> " << endl << endl;
  T.insertBST(8); T.inorder();
  T.insertBST(18); T.inorder();
  T.insertBST(11); T.inorder();
  T.insertBST(5); T.inorder();
  T.insertBST(15); T.inorder();
  T.insertBST(4); T.inorder();
  T.insertBST(9); T.inorder();
  T.insertBST(1); T.inorder();
  T.insertBST(7); T.inorder();
  T.insertBST(17); T.inorder();
  T.insertBST(6); T.inorder();
  T.insertBST(14); T.inorder();
  T.insertBST(10); T.inorder();
  T.insertBST(3); T.inorder();
  T.insertBST(19); T.inorder();
  T.insertBST(20); T.inorder();

  cout << endl << " <<<<<< deleteBST >>>>>>> " << endl << endl;
  T.deleteBST(8); T.inorder();
  T.deleteBST(18); T.inorder();
  T.deleteBST(11); T.inorder();
  T.deleteBST(5); T.inorder();
  T.deleteBST(15); T.inorder();
  T.deleteBST(4); T.inorder();
  T.deleteBST(9); T.inorder();
  T.deleteBST(1); T.inorder();
  T.deleteBST(7); T.inorder();
  T.deleteBST(17); T.inorder();
  T.deleteBST(6); T.inorder();
  T.deleteBST(14); T.inorder();
  T.deleteBST(10); T.inorder();
  T.deleteBST(3); T.inorder();
  T.deleteBST(19); T.inorder();
  T.deleteBST(20); T.inorder();

  cout << endl << " <<<<<< insertBST >>>>>>> " << endl << endl;
  T.insertBST(8); T.inorder();
  T.insertBST(18); T.inorder();
  T.insertBST(11); T.inorder();
  T.insertBST(5); T.inorder();
  T.insertBST(15); T.inorder();
  T.insertBST(4); T.inorder();
  T.insertBST(9); T.inorder();
  T.insertBST(1); T.inorder();
  T.insertBST(7); T.inorder();
  T.insertBST(17); T.inorder();
  T.insertBST(6); T.inorder();
  T.insertBST(14); T.inorder();
  T.insertBST(10); T.inorder();
  T.insertBST(3); T.inorder();
  T.insertBST(19); T.inorder();
  T.insertBST(20); T.inorder();


  cout << endl << " <<<<<< invers deleteBST >>>>>>> " << endl << endl;
  T.deleteBST(20); T.inorder();
  T.deleteBST(19); T.inorder();
  T.deleteBST(3); T.inorder();
  T.deleteBST(10); T.inorder();
  T.deleteBST(14); T.inorder();
  T.deleteBST(6); T.inorder();
  T.deleteBST(17); T.inorder();
  T.deleteBST(7); T.inorder();
  T.deleteBST(1); T.inorder();
  T.deleteBST(9); T.inorder();
  T.deleteBST(4); T.inorder();
  T.deleteBST(15); T.inorder();
  T.deleteBST(5); T.inorder();
  T.deleteBST(11); T.inorder();
  T.deleteBST(18); T.inorder();
  T.deleteBST(8); T.inorder();

}
