#pragma once
#include <iostream>
#include <string>

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

