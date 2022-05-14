#pragma once
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

const int LEVEL = 1, RLEVEL = 2, PRE = 3;
namespace ariel{

    class Node{

        private:
            std::string data;
            Node * parent;
            std::vector<Node *> subs;
        public:
            //constructors
            Node(std::string data, Node * p):data{std::move(data)}, parent{p}{};
            //methods
            void set_data(std::string data);
            std::string get_data() const;
            std::vector<Node*> & get_subs(){return subs;}
            std::vector<Node *>::iterator child_itr_begin();
            std::vector<Node *>::iterator child_itr_end();

            void add_child(Node * child);

            //operators
            friend std::ostream& operator<<(std::ostream& os,  Node* n){
                    os<<n->get_data();
                    return os;
            }
    };

    class OrgChart{

        private:
            Node * root;
            std::vector<Node*> pre_order_vec, level_order_vec, reverse_order_vec;
            bool pre_changed, level_changed, reverse_changed;
            
            //Ordered vecotr fill
            void pre_fill(Node *);
            void level_fill(Node *);
            void reverse_fill(Node *);
        public:
            
            OrgChart():root{nullptr}, pre_changed{false}, level_changed{false}, reverse_changed{false}{};

            //adding methods
            OrgChart & add_root(std::string rstr);
            OrgChart & add_sub(std::string manager, std::string subordinate);
            
            //utility methods
            Node * find(Node * root, std::string tofind) const;
            void print(Node * root);

            //iterator generators
            std::vector<Node*>::iterator begin_preorder();
            std::vector<Node*>::iterator end_preorder();
            std::vector<Node*>::iterator begin_level_order();
            std::vector<Node*>::iterator end_level_order();
            std::vector<Node*>::iterator begin_reverse_order();
            std::vector<Node*>::iterator end_reverse_order();
            
            

            

    };

    class node_itr{
        
        private:
            std::vector<Node*> nodes;
            //filler functions: fill the vector in the required order
            void level(Node * root);
            void rlevel(Node * root);
            void pre(Node * root);
        public:
            node_itr(Node * root, int order);

    };
}