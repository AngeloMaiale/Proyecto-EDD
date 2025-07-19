#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>
class Node {
private:
    T content;
    Node<T>* link;
public:
    Node(T, Node<T>* = nullptr);
    ~Node();

    T getContent();
    Node<T>* getLink();
    void setLink(Node<T>*);
    void setContent(T);
    void Mostrar();
};

template <class T>
Node<T>::Node(T c, Node<T>* l) : content(c), link(l) {}

template <class T>
Node<T>::~Node() {}

template <class T>
T Node<T>::getContent() { return content; }

template <class T>
Node<T>* Node<T>::getLink() { return link; }

template <class T>
void Node<T>::setLink(Node<T>* l) { link = l; }

template <class T>
void Node<T>::Mostrar() {
    std::cout << content << "----------------------\n";
}

template <class T>
class Trees {
private:
    Node<T>* root;
public:
    Trees();
    ~Trees();

    bool Vacio();
    void insertar(T content);
    void MostrarInOrden();
    void MostrarPreOrden();
    void MostrarPostOrden();
    Node<T>* buscar(T content);
    void deleteNode(T content);
    void updateNode(T oldContent, T newContent);
};

template <class T>
Trees<T>::Trees() : root(nullptr) {}

template <class T>
Trees<T>::~Trees() {
}

template <class T>
bool Trees<T>::Vacio() {
    return root == nullptr;
}

template <class T>
void Trees<T>::insertar(T content) {
}

template <class T>
void Trees<T>::MostrarInOrden() {
}

template <class T>
void Trees<T>::MostrarPreOrden() {
}

template <class T>
void Trees<T>::MostrarPostOrden() {
}

template <class T>
Node<T>* Trees<T>::buscar(T content) {
}

template <class T>
void Trees<T>::deleteNode(T content) {
}

template <class T>
void Trees<T>::updateNode(T oldContent, T newContent) {
    Node<T>* node = buscar(oldContent);
    if (node != nullptr) node->setContent(newContent);
}

struct Mago {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_father;
    bool is_dead;
    string type_magic;
    bool is_owner;
};
struct ChildNode {
    struct TreeNode* child;
    ChildNode* next;
};

ChildNode* createChildNode(TreeNode* child) {
    ChildNode* node = new ChildNode;
    node->child = child;
    node->next = nullptr;
    return node;
};

struct TreeNode {
    Mago content;
    ChildNode* children;

    TreeNode(Mago w);
    void display(int depth = 0);
};

TreeNode::TreeNode(Mago w) {
    content = w;
    children = nullptr;
}

void TreeNode::display(int depth) {
    for (int i = 0; i < depth; ++i) cout << "    ";
    cout << content.name << " " << content.last_name << " (ID: " << content.id << ")"
         << " | Magia: " << content.type_magic << " | Edad: " << content.age
         << " | Dueno: " << (content.is_owner ? "Si" : "No") << "\n";
    ChildNode* current = children;
    while (current) {
        current->child->display(depth + 1);
        current = current->next;
    }
}

class MagicTree {
private:
    TreeNode* root;
    TreeNode* nodes[100]; 
    int total;

public:
    MagicTree();
    void buildTree(Mago*, int);
    void displayTree();
    TreeNode* getRoot();
    TreeNode* findByID(int);
};

MagicTree::MagicTree() {
    root = nullptr;
    total = 0;
    for (int i = 0; i < 100; ++i) nodes[i] = nullptr;
}

TreeNode* MagicTree::findByID(int id) {
    for (int i = 0; i < total; ++i)
        if (nodes[i] && nodes[i]->content.id == id)
            return nodes[i];
    return nullptr;
}

void MagicTree::buildTree(Mago* list, int count) {
    for (int i = 0; i < count; ++i) {
        nodes[total++] = new TreeNode(list[i]);
    }

    for (int i = 0; i < total; ++i) {
        Mago& w = nodes[i]->content;
        if (w.id_father == 0) {
            root = nodes[i];
        } else {
            TreeNode* parent = findByID(w.id_father);
            if (parent) {
                ChildNode* childNode = createChildNode(nodes[i]);
                if (!parent->children) {
                    parent->children = childNode;
                } else {
                    ChildNode* current = parent->children;
                    while (current->next)
                        current = current->next;
                    current->next = childNode;
                }
            }
        }
    }
}

TreeNode* MagicTree::getRoot() {
    return root;
}

void MagicTree::displayTree() {
    if (root) root->display();
    else cout << "⚠️ arbol magico vacio.\n";
}

int convertirSeguro(const string& str, bool permitirVacio = false) {
    if (str.empty()) return permitirVacio ? 0 : -1;
    try {
        return stoi(str);
    } catch (...) {
        return -1;
    }
}

void mostrarSucesionViva(TreeNode* node, int depth = 0) {
    if (!node) return;

    if (!node->content.is_dead) {
        for (int i = 0; i < depth; ++i) cout << "    ";
        cout << node->content.name << " " << node->content.last_name
             << " (ID: " << node->content.id << ") | Magia: " << node->content.type_magic
             << " | Edad: " << node->content.age
             << " | Dueño: " << (node->content.is_owner ? "Sí" : "No") << "\n";
    }

    ChildNode* current = node->children;
    while (current) {
        mostrarSucesionViva(current->child, depth + 1);
        current = current->next;
    }
}

