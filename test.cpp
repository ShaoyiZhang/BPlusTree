#include "BTree.h"

int main(){
    BTree tree = BTree();
    tree.Insert("saber",123);
    tree.Insert("lancer", 234);
    tree.Insert("caster", 345);
    tree.Insert("archer", 456);
    tree.Insert("assassin", 567);
    tree.Insert("berserker", 678);
    tree.Insert("rider", 789);
    //tree.Insert("teacher", 910);
    tree.PrintAll(tree.GetRoot());
    cout << tree.GetRoot()->GetOccupancy() << endl;
}