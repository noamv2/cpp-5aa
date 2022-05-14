#include "olgOrg.hpp"

using namespace ariel;



// Node class methods
void Node::set_data(std::string data){
    this->data = data;
}

std::string Node::get_data() const{
    return this->data;
}

void Node::add_child(Node * child){
    subs.push_back(child);
}

std::vector<Node *>::iterator Node::child_itr_begin(){   
    return subs.begin();
}
std::vector<Node *>::iterator Node::child_itr_end(){
    return subs.end();
}


OrgChart & OrgChart::add_root(std::string rstr){
    pre_changed = true; 
    level_changed = true; 
    reverse_changed = true;
    //The tree is empty
    if(!root){
        root = new Node(rstr, nullptr);
        return *this;
    }

    // The tree contain a root 
    root->set_data(rstr);
    return *this;

}

Node * OrgChart::find(Node * root, std::string tofind) const{
    
    if(!root){
        return nullptr;
    }

    if(root->get_data() == tofind){
        return root;
    }

    //search recursively in the root's children
    Node *ptr;
    for(auto it = root-> child_itr_begin(); it != root->child_itr_end(); ++it){
        
        ptr = find(*it, tofind);
        if(ptr){// we found instace of 'tofind'
            return ptr;
        }
    }

    return nullptr;
}

OrgChart & OrgChart::add_sub(std::string manager, std::string subordinate){
    pre_changed = true;
    level_changed = true; 
    reverse_changed = true;
    // Look for the manager in the orgchart
    Node * mang = find(root, manager);
    if(!mang){
        throw std::invalid_argument("Manager does not exsits");
    } 
    //create new node for the employye

    mang->add_child(new Node(subordinate, mang));
    return *this;
}

void OrgChart::print(Node * root){

    if(!root){return;}
    std::queue<Node*> que;
    que.push(root);

    while(!que.empty()){
        // push the front of the queue to the vector
        Node *curr = que.front();
        level_order_vec.push_back(curr);
        que.pop();

        //enque the children
        for(auto it = curr->child_itr_begin(); it != curr->child_itr_end(); ++it){
            que.push(*it);
        }
    }
    
    
}

void OrgChart::pre_fill(Node * root){
    if(!root){
        return;
    }

    pre_order_vec.push_back(root);
    for(auto it = root->child_itr_begin(); it != root->child_itr_end(); ++it){
        pre_fill(*it);
    }

}

void OrgChart::level_fill(Node * root){ //fill both the level and the reverse level order
    //clear the containers
    level_order_vec.clear();
    std::queue<Node*> que;
    level_changed = false;

    if(!root){return;}

    que.push(root);

    while(!que.empty()){
        // push the front of the queue to the vector
        Node *curr = que.front();
        level_order_vec.push_back(curr);
        que.pop();

        //enque the children
        for(auto it = curr->child_itr_begin(); it != curr->child_itr_end(); ++it){
            que.push(*it);
        }
    }
}

void OrgChart::reverse_fill(Node * root){ //fill both the level and the reverse level order
    //clear the containers
    level_order_vec.clear();
    std::queue<Node*> que;
    std::stack<Node*> st;

    reverse_changed = false;

    if(!root){return;}

    que.push(root);

    while(!que.empty()){
        // push the front of the queue to the vector
        root = que.front();
        que.pop();
        st.push(root);

        //enque the children
        for(int i = root->get_subs().size() - 1; i >= 0; i--){
            que.push(root->get_subs().at(static_cast<size_t>(i)));
        }
    }

    while(!st.empty()){
        //insert the element to the correct vector
        reverse_order_vec.push_back(st.top());
        st.pop();
    }

}

std::vector<Node*>::iterator OrgChart::begin_preorder(){
    //update the pre order vector if needed
    if(pre_changed){
        pre_order_vec.clear();
        pre_fill(root);
    }
    return pre_order_vec.begin();
}

std::vector<Node*>::iterator OrgChart::end_preorder(){
    //update the pre order vector if needed
    if(pre_changed){
        pre_order_vec.clear();
        pre_fill(root);
    }
    return pre_order_vec.end();
}

std::vector<Node*>::iterator OrgChart::begin_level_order(){
    if(level_changed){
        //fill the vector with the new level order
        level_fill(root);
    }
    return level_order_vec.begin();
}

std::vector<Node*>::iterator OrgChart::end_level_order(){    
    if(level_changed){
        //fill the vector with the new level order
        level_fill(root);
    }
    return level_order_vec.end();
}

std::vector<Node*>::iterator OrgChart::begin_reverse_order(){    
    if(reverse_changed){
        //fill the vector with the new level order
        reverse_fill(root);
    }
    
    
    return reverse_order_vec.begin();
}

std::vector<Node*>::iterator OrgChart::end_reverse_order(){    
    if(reverse_changed){
        //fill the vector with the new level order
        reverse_fill(root);
    }
    return reverse_order_vec.end();
}
