#include <iostream>
#include "tree.h"
using namespace std;

void RBTree::insert(int key) {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    //y - родитель x
    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->data < y->data) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    //Если новая вершина - корень, то просто завершаем
    if (node->parent == nullptr) {
        node->color = 0;
        return;
    }

    //Если дед пустой, то просто завершаем
    if (node->parent->parent == nullptr) {
        return;
    }

    //Балансировка
    fixInsert(node);
}

void RBTree::fixInsert(NodePtr k) {
    NodePtr u;
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            //Для правой стороны
            u = k->parent->parent->left;
            if (u->color == 1) {
                // 3.1
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    // 3.2.2
                    k = k->parent;
                    rightRotate(k);
                }
                // 3.2.1
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        }
        else {
            //для левой стороны
            u = k->parent->parent->right;

            if (u->color == 1) {
                // 3.1
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    // 3.2.2
                    k = k->parent;
                    leftRotate(k);
                }
                // 3.2.1
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 0;
}

void RBTree::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}

void RBTree::deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        cout << "Couldn't find key in the tree" << endl;
        return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) { //Этот блок кода определяет, какой тип потомков есть у узла z.
        // Если у узла нет левого потомка, то x присваивается правый потомок z. Если у узла нет правого потомка, то x присваивается левый потомок z
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else {
        y = minimum(z->right);// В этой строке переменной y присваивается минимальный узел из правого поддерева узла z.
        // Это делается для того, чтобы найти наименьший узел, который будет являться следующим после узла z в порядке возрастания ключей.
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) { //В этой части кода мы работаем с поддеревом, которое будет заменять удаляемый узел z.
            // Если у узла y нет левого потомка, то мы просто присваиваем правого потомка узла y переменной x.
            //Если у узла y есть левый потомок, то мы используем функцию rbTransplant для замены узла y его правым потомком.
            // Затем правый потомок узла y становится правым потомком узла z.
            x->parent = y;
        }
        else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y); //В этой части кода происходит замена узла z узлом y. Мы используем функцию rbTransplant для переноса
        // узла y в позицию узла z.Затем левый потомок узла z становится левым потомком узла y. При этом обновляются ссылки на родителей.
        //Цвет узла y устанавливается равным цвету узла z. Это важно для сохранения инвариантов красно-черного дерева после удаления узла
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
        fixDelete(x);
    }
}

void RBTree::fixDelete(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
        //При левой части
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == 1) {
                //  3.1
                s->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == 0 && s->right->color == 0) {
                // 3.2
                s->color = 1;
                x = x->parent;
            }
            else {
                if (s->right->color == 0) {
                    //  3.3
                    s->left->color = 0;
                    s->color = 1;
                    rightRotate(s);
                    s = x->parent->right;
                }

                //  3.4
                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            //При правой части
            s = x->parent->left;
            if (s->color == 1) {
                //  3.1
                s->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if ((s->right->color == 0) && (s->right->color == 0)) {
                //  3.2
                s->color = 1;
                x = x->parent;
            }
            else {
                if (s->left->color == 0) {
                    //  3.3
                    s->right->color = 0;
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }

                //  3.4
                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}

int main() {
    RBTree bst;
    bst.insert(8);
    bst.prettyPrint();
    cout << endl;
    bst.insert(18);
    bst.prettyPrint();
    cout << endl;
    bst.insert(5);
    bst.prettyPrint();
    cout << endl;
    bst.insert(15);
    bst.prettyPrint();
    cout << endl;
    bst.insert(17);
    bst.prettyPrint();
    cout << endl;
    bst.insert(25);
    bst.prettyPrint();
    cout << endl;
    bst.insert(40);
    bst.prettyPrint();
    cout << endl;
    bst.insert(80);
    bst.prettyPrint();
    cout << endl;
    bst.deleteNode(25);
    bst.prettyPrint();
    cout << endl;
    bst.deleteNode(17);
    bst.insert(25);
    bst.insert(17);
    bst.deleteNode(15);
    bst.insert(15);
    bst.insert(20);
    bst.insert(10);
    bst.insert(6);
    bst.prettyPrint();
    cout << endl;
    (bst.searchTree(22)) ? cout << "success" : cout << "not found";
    cout << endl;
    cout << "minimum:" << bst.minimum(bst.getRoot())->data << endl;
    cout << "maxsimum:" << bst.maximum(bst.getRoot())->data << endl;
    cout << "nearest larger:" << bst.findClosestGreater(8)->data << endl;
    cout << "nearest smaller:" << bst.findClosestSmaller(8)->data << endl;
    return 0;
}