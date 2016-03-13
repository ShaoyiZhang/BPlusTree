#include "BTree.h"

int main(){
    BTree tree = BTree();
    tree.Insert("saber",123);
    tree.PrintAll(tree.GetRoot());
}