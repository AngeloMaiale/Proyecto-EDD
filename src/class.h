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
    bool hasLivingChildren();
    TreeNode* findFirstLivingChildWithMagic(const string& magicType);
    TreeNode* findFirstLivingMaleChild();
    TreeNode* findYoungestLivingFemale();
};

TreeNode::TreeNode(Mago w) {
    content = w;
    children = nullptr;
}

bool TreeNode::hasLivingChildren() {
    ChildNode* current = children;
    while (current) {
        if (!current->child->content.is_dead) return true;
        current = current->next;
    }
    return false;
}

TreeNode* TreeNode::findFirstLivingChildWithMagic(const string& magicType) {
    ChildNode* current = children;
    while (current) {
        if (!current->child->content.is_dead && current->child->content.type_magic == magicType) {
            return current->child;
        }
        current = current->next;
    }
    return nullptr;
}

TreeNode* TreeNode::findFirstLivingMaleChild() {
    ChildNode* current = children;
    while (current) {
        if (!current->child->content.is_dead && current->child->content.gender == 'M') {
            return current->child;
        }
        current = current->next;
    }
    return nullptr;
}

TreeNode* TreeNode::findYoungestLivingFemale() {
    TreeNode* youngest = nullptr;
    ChildNode* current = children;
    while (current) {
        if (!current->child->content.is_dead && current->child->content.gender == 'F') {
            if (!youngest || current->child->content.age < youngest->content.age) {
                youngest = current->child;
            }
        }
        current = current->next;
    }
    return youngest;
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
    TreeNode* findCurrentOwner();
    TreeNode* findNewOwnerAccordingToRules();
    TreeNode* findCompanion(TreeNode* node);
    TreeNode* findMasterCompanion(TreeNode* node);
    TreeNode* findYoungestFemaleWithMixedMagic();
    void saveNodeToFile(TreeNode* node, ofstream& file);
    void clearChildren(ChildNode* children);

public:
    MagicTree();
    ~MagicTree();

    void buildTree(Mago* list, int count);
    void displayTree();
    TreeNode* getRoot();
    TreeNode* findByID(int id);
    bool insertMago(Mago nuevo);
    bool deleteMago(int id);
    bool updateMago(Mago actualizado);
    void autoAssignOwner();
    void getInheritedSpells(int id, string spells[], int& count);
    void saveToCSV(const string& filename);
};

MagicTree::MagicTree() {
    root = nullptr;
    total = 0;
    for (int i = 0; i < 100; ++i) nodes[i] = nullptr;
}

MagicTree::~MagicTree() {
    for (int i = 0; i < total; i++) {
        if (nodes[i]) {
            clearChildren(nodes[i]->children);
            delete nodes[i];
        }
    }
}

void MagicTree::clearChildren(ChildNode* children) {
    while (children) {
        ChildNode* temp = children;
        children = children->next;
        delete temp;
    }
}

TreeNode* MagicTree::findByID(int id) {
    for (int i = 0; i < total; i++)
        if (nodes[i] && nodes[i]->content.id == id)
            return nodes[i];
    return nullptr;
}

void MagicTree::buildTree(Mago* list, int count) {
    for (int i = 0; i < count; i++) {
        nodes[total++] = new TreeNode(list[i]);
    }

    for (int i = 0; i < total; i++) {
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
    autoAssignOwner();
}

bool MagicTree::insertMago(Mago nuevo) {
    if (total >= 100 || findByID(nuevo.id) != nullptr) {
        return false;
    }
    
    nodes[total++] = new TreeNode(nuevo);
    
    if (nuevo.id_father != 0) {
        TreeNode* parent = findByID(nuevo.id_father);
        if (parent) {
            ChildNode* childNode = createChildNode(nodes[total-1]);
            if (!parent->children) {
                parent->children = childNode;
            } else {
                ChildNode* current = parent->children;
                while (current->next)
                    current = current->next;
                current->next = childNode;
            }
        }
    } else if (root == nullptr) {
        root = nodes[total-1];
    }
    
    autoAssignOwner();
    return true;
}

bool MagicTree::deleteMago(int id) {
    if (id == 0 || findByID(id) == root) return false;
    
    TreeNode* nodeToDelete = nullptr;
    int indexToDelete = -1;
    
    for (int i = 0; i < total; i++) {
        if (nodes[i] && nodes[i]->content.id == id) {
            nodeToDelete = nodes[i];
            indexToDelete = i;
            break;
        }
    }
    
    if (!nodeToDelete || nodeToDelete->hasLivingChildren()) {
        return false;
    }
    
    TreeNode* parent = findByID(nodeToDelete->content.id_father);
    if (parent) {
        ChildNode* prev = nullptr;
        ChildNode* current = parent->children;
        
        while (current) {
            if (current->child == nodeToDelete) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    parent->children = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }
    }
    
    delete nodeToDelete;
    nodes[indexToDelete] = nullptr;
    autoAssignOwner();
    return true;
}

bool MagicTree::updateMago(Mago actualizado) {
    TreeNode* node = findByID(actualizado.id);
    if (!node) return false;
    
    node->content = actualizado;
    autoAssignOwner();
    return true;
}

TreeNode* MagicTree::findCurrentOwner() {
    for (int i = 0; i < total; ++i) {
        if (nodes[i] && nodes[i]->content.is_owner) {
            return nodes[i];
        }
    }
    return nullptr;
}

TreeNode* MagicTree::findNewOwnerAccordingToRules() {
    TreeNode* current = findCurrentOwner();
    if (!current || !current->content.is_dead) return nullptr;
    if (current->content.age > 70) {
        ChildNode* hijos = current->children;
        TreeNode* igual = nullptr;
        TreeNode* masViejo = nullptr;

        while (hijos) {
            TreeNode* hijo = hijos->child;
            Mago& m = hijo->content;

            if (!m.is_dead) {
                if (m.type_magic == current->content.type_magic) return hijo;
                if (!masViejo || m.age > masViejo->content.age) masViejo = hijo;
            }
            hijos = hijos->next;
        }
        if (masViejo) return masViejo;
    }
    TreeNode* elemental = current->findFirstLivingChildWithMagic("elemental");
    TreeNode* unique = current->findFirstLivingChildWithMagic("unique");
    TreeNode* mixed = current->findFirstLivingChildWithMagic("mixed");
    TreeNode* hombre = current->findFirstLivingMaleChild();

    if (elemental) return elemental;
    if (unique) return unique;
    if (mixed) return mixed;
    if (hombre) return hombre;
    TreeNode* maestro = findByID(current->content.id_father);
    if (maestro) {
        ChildNode* hermanos = maestro->children;
        while (hermanos) {
            TreeNode* comp = hermanos->child;
            if (comp != current && !comp->content.is_dead &&
                comp->content.type_magic == current->content.type_magic) {
                return comp;
            }
            hermanos = hermanos->next;
        }
        hermanos = maestro->children;
        while (hermanos) {
            TreeNode* comp = hermanos->child;
            if (comp != current) {
                TreeNode* elementalComp = comp->findFirstLivingChildWithMagic("elemental");
                TreeNode* uniqueComp = comp->findFirstLivingChildWithMagic("unique");
                if (elementalComp) return elementalComp;
                if (uniqueComp) return uniqueComp;
            }
            hermanos = hermanos->next;
        }
    }
    TreeNode* abuelo = maestro ? findByID(maestro->content.id_father) : nullptr;
    if (abuelo) {
        ChildNode* tios = abuelo->children;
        while (tios) {
            TreeNode* tio = tios->child;
            if (tio != maestro && !tio->content.is_dead) return tio;
            tios = tios->next;
        }
    }
    TreeNode* mejorCandidata = nullptr;
    for (int i = 0; i < total; ++i) {
        TreeNode* nodo = nodes[i];
        Mago& m = nodo->content;
        if (!m.is_dead && m.gender == 'F' && m.type_magic == "mixed" && nodo->children) {
            if (!mejorCandidata || m.age < mejorCandidata->content.age)
                mejorCandidata = nodo;
        }
    }

    if (mejorCandidata) return mejorCandidata;
    for (int i = 0; i < total; ++i) {
        TreeNode* nodo = nodes[i];
        Mago& m = nodo->content;
        if (!m.is_dead && m.gender == 'F') {
            if (!mejorCandidata || m.age < mejorCandidata->content.age)
                mejorCandidata = nodo;
        }
    }

    return mejorCandidata;
}


void MagicTree::autoAssignOwner() {
    TreeNode* currentOwner = findCurrentOwner();

    if (!currentOwner) {
        std::cout << "No hay dueno actual registrado.\n";
        return;
    }
    if (!currentOwner->content.is_dead) {
        std::cout << "El dueno actual (" << currentOwner->content.name << ") esta vivo. No se realiza sucesion.\n";
        return;
    }

    TreeNode* newOwner = findNewOwnerAccordingToRules();
    currentOwner->content.is_owner = false;

    if (newOwner) {
        newOwner->content.is_owner = true;
        std::cout << "Nuevo dueno asignado: " << newOwner->content.name
                  << " (ID: " << newOwner->content.id << ", Magia: "
                  << newOwner->content.type_magic << ", Edad: "
                  << newOwner->content.age << ")\n";
    } else {
        std::cout << "No se encontro nuevo dueno segun las reglas.\n";
    }
}




void MagicTree::getInheritedSpells(int id, string spells[], int& count) {
    count = 0;
    TreeNode* current = findByID(id);
    
    while (current && count < 100) {
        if (current->content.type_magic != "no_magic") {
            spells[count++] = current->content.type_magic;
        }
        current = findByID(current->content.id_father);
    }
}

void MagicTree::saveNodeToFile(TreeNode* node, ofstream& file) {
    if (!node) return;
    
    file << node->content.id << ","
         << node->content.name << ","
         << node->content.last_name << ","
         << node->content.gender << ","
         << node->content.age << ","
         << node->content.id_father << ","
         << (node->content.is_dead ? "1" : "0") << ","
         << node->content.type_magic << ","
         << (node->content.is_owner ? "1" : "0") << "\n";
    
    ChildNode* current = node->children;
    while (current) {
        saveNodeToFile(current->child, file);
        current = current->next;
    }
}

void MagicTree::saveToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo para guardar.\n";
        return;
    }
    
    file << "id,name,last_name,gender,age,id_father,is_dead,type_magic,is_owner\n";
    saveNodeToFile(root, file);
    file.close();
}

TreeNode* MagicTree::getRoot() {
    return root;
}

void MagicTree::displayTree() {
    if (root) root->display();
    else cout << "Arbol magico vacio.\n";
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
             << " | Dueno: " << (node->content.is_owner ? "Si" : "No") << "\n";
    }

    ChildNode* current = node->children;
    while (current) {
        mostrarSucesionViva(current->child, depth + 1);
        current = current->next;
    }
}