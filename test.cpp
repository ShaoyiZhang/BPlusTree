#include "BTree.h"

int main(){
    BTree tree = BTree();
    tree.Insert("saber",123);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("lancer", 234);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("caster", 345);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("archer", 456);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("assassin", 567);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("berserker", 678);
    tree.PrintAll(tree.GetRoot());
    cout << tree.GetRoot()->GetOccupancy() << endl;
    cout<<endl;
    tree.Insert("rider", 789);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("teacher", 910);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("gaotian", 1789);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("hexiaohe", 111);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("az",11121);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    tree.Insert("av",999);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
    cout << tree.GetRoot()->GetOccupancy() << endl;
}