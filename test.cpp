#include "BTree.h"

int main(){
    BTree tree = BTree();
    tree.Insert("saber",123);
    tree.Insert("lancer", 234);
    tree.Insert("caster", 345);
    tree.Insert("archer", 456);
    tree.PrintAll(tree.GetRoot());
}