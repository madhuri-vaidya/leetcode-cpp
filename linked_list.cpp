/* Linked List Problems */

/* Design a Singly Linked List */
class Node {
public:
    int val;
    Node* next;
    Node* prev;
    Node* child;
    Node* random;
    
    Node() : val(0), next(nullptr) {}
    Node(int x) : val(x), next(nullptr) {}
    Node(int x, Node* next_node) : val(x), next(next_node) {}
};

class MyLinkedList {
private:
    Node* head;
    
public:
    MyLinkedList() : head(nullptr) {}
    
    int get(int index) {
        Node* temp = head;
        int i = 0;
        
        while(temp) {
            if(i == index) { return temp->val; }
            temp = temp->next;
            i++;
        }
        return -1;
    }
    
    void addAtHead(int val) {
        Node* temp = new Node(val, head);
        head = temp;
    }
    
    void addAtTail(int val) {
        Node* temp = head;
        
        if(!head) { addAtHead(val); return; }
        
        Node* to_add = new Node(val);
        
        while(temp) {
            if(temp->next == nullptr) { temp->next = to_add; return; }
            temp = temp->next;
        }
    }
    
    void addAtIndex(int index, int val) {
        Node* temp = head;
        
        if(index == 0) { addAtHead(val); return; }
        
        Node* to_add = new Node(val);
        int i = 0;
        
        while(temp) {
            if(i == index - 1) {
                to_add->next = temp->next;
                temp->next = to_add;
                return;
            }
            temp = temp->next; 
            i++;
        }
    }
    
    void deleteAtIndex(int index) {
        Node* temp = head;
        int i = 0;
        
        if((index == 0) && head) { head = temp->next; return; }
        
        while(temp && (temp->next)) {
            if(i == index - 1) { temp->next = temp->next->next; return; }
            temp = temp->next;
            i++;
        }
    }
};


class Solution {
public:

    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    /* Linked List Cycle
    Given head, the head of a linked list, determine if the linked list has a cycle in it.

    There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

    Return true if there is a cycle in the linked list. Otherwise, return false.
    */
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        while(fast && (fast->next != nullptr)) {
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast) { return true; }
        }
        
        return false;
    }


    /* Linked List Cycle II
    Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

    There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.

    Do not modify the linked list.
    */
   ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        bool is_chain = false;
        
        while(fast && (fast->next != nullptr)) {
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast) { is_chain = true; break; }
        }
        
        if(is_chain) {
            slow = head;
            
            while(slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
        
        return nullptr;
    }


    /* Insertion of 2 Linked Lists
    Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.
    */
   ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *ptrA = headA, *ptrB = headB;
        int nodesA = 1, nodesB = 1;
        
        //Find if they are linked
        while(ptrA->next != nullptr) {
            ptrA = ptrA->next;
            nodesA++;
        }
        
        while(ptrB->next != nullptr) {
            ptrB = ptrB->next;
            nodesB++;
        }
        
        if(ptrA != ptrB) { return nullptr; }
        
        //Find where they are linked
        if(nodesA == nodesB) {
            ptrA = headA;
            ptrB = headB;
        }
        
        if(nodesA > nodesB) {
            int ctr = 0;
            ptrA = headA;
            ptrB = headB;
            while(ctr < nodesA - nodesB) {
                ptrA = ptrA->next;
                ctr++;
            }
        }
        
        if(nodesA < nodesB) {
            int ctr = 0;
            ptrA = headA;
            ptrB = headB;
            while(ctr < nodesB - nodesA) {
                ptrB = ptrB->next;
                ctr++;
            }
        }
        
        while(ptrA != ptrB) {
            ptrA = ptrA->next;
            ptrB = ptrB->next;
        }
        
        return ptrA;   
    }


    /* Remove Nth Node from End of List
    Given the head of a linked list, remove the nth node from the end of the list and return its head.
    */
   ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *front = head, *back = head;
        int delay = 0;
        
        if(head->next == nullptr) { head = nullptr; return head; }
        
        if(head->next->next == nullptr) {
            if(n == 1) { head->next = nullptr; }
            if(n == 2) { head = head->next; }
            return head;
        }
        
        while(front->next) {
            front = front->next;
            if(delay >= n) { back = back->next; }
            else { delay++; }
        }
        
        if(delay < n) { head = head->next; return head; }
        
        if(back->next->next) { back->next = back->next->next; }
        else { back->next = nullptr; }
        
        return head;
    }


    /* Reverse Singly Linked List
    Given the head of a singly linked list, reverse the list, and return the reversed list.
    */
   ListNode* iterativeApproach(ListNode* head) {
        ListNode *new_head = head, *temp;
        
        if((!head) || (head->next == nullptr)) { return head; }
        
        while(head->next) {
            temp = head->next;
            head->next = head->next->next;
            temp->next = new_head;
            new_head = temp;
        }
        
        return new_head;
    }
    
    ListNode* recursiveApproach(ListNode* head) {
        if((!head) || (head->next == nullptr)) { return head; }
        
        ListNode *rest = recursiveApproach(head->next);
        head->next->next = head;
        head->next = nullptr;
        
        return rest;
    }
    
    ListNode* reverseList(ListNode* head) {
        //return iterativeApproach(head);
        return recursiveApproach(head);
    }


    /* Remove Linked List Elements
    Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.
    */
   ListNode* removeElements(ListNode* head, int val) {
        ListNode *temp = head;
        
        if(!head) { return head; }
        
        while(head->val == val) {
            if(head->next) { head = head->next; }
            else { head = nullptr; return head; }
        }
        
        while(temp->next) {
            if(temp->next->val == val) { temp->next = temp->next->next; }
            else { temp = temp->next; }
        }
        
        return head;
    }


    /* Odd Even Linked List
    Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.

    The first node is considered odd, and the second node is even, and so on.

    Note that the relative order inside both the even and odd groups should remain as it was in the input.

    You must solve the problem in O(1) extra space complexity and O(n) time complexity.
    */
   ListNode* oddEvenList(ListNode* head) {
        ListNode *end = head, *temp = head;
        int total_nodes = 1, node = 1;
        
        if(!head) { return head; }
        
        //Traverse the 'end' pointer to end of list
        while(end->next) { end = end->next; total_nodes++; }
        
        //Move the even nodes to end of list
        while(node <= (total_nodes/2)) {
            end->next = temp->next;
            temp->next = temp->next->next;
            end = end->next;
            end->next = nullptr;
            
            temp = temp->next;
            node++;
        }
        return head;
    }


    /* Palindrome Linked List
    Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
    */
   bool isPalindrome(ListNode* head) {
        ListNode *slow = head, *fast = head, *new_head = head, *temp;
        bool even_nodes = false;
        
        //Case of 0, 1 or 2 nodes
        if(!head) { return false; }
        if(head->next == nullptr) { return true; }
        if(head->next->next == nullptr) {
            if(head->val == head->next->val) { return true; }
            else { return false; }
        }
        
        //Find middle and end node
        while(fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if((fast->next) && (fast->next->next == nullptr)) { 
                fast = fast->next;
                slow = slow->next;
                even_nodes = true;
            }
        }
        
        if(head->val != fast->val) { return false; }
        
        //Reverse first half of list
        while(head->next != slow) {
            temp = head->next;
            head->next = head->next->next;
            temp->next = new_head;
            new_head = temp;
        }
        
        //Check if the two halves are same
        if(even_nodes) { fast = slow; }
        else { fast = slow->next; }
        slow = new_head;
        while(fast) {
            if(slow->val != fast->val) { return false; }
            slow = slow->next;
            fast = fast->next;
        }
        
        return true;
    }


    /* Merge 2 Sorted Lists
    You are given the heads of two sorted linked lists list1 and list2.

    Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.

    Return the head of the merged linked list.
    */
   ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *t1 = list1, *t2 = list2, *merged_head = list1, *temp;
        
        if((list1 == nullptr) && (list2 == nullptr)) { return nullptr; }
        if((list1 == nullptr) && (list2 != nullptr)) { return list2; }
        if((list1 != nullptr) && (list2 == nullptr)) { return list1; }
        
        while(t1) {
            // Insert t2 before t1 and move t1 back to inserted node
            if(t1->val >= t2->val) {
                temp = t2->next;
                t2->next = t1;
                
                // Case for t1 being head node
                if(merged_head == t1) { t1 = t2; merged_head = t1; }
                else { t1 = t2; }
                
                t2 = temp;
            }
            
            t1 = t1->next;
        }
        
        return merged_head;
    }


    /* Add 2 Numbers
    You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

    You may assume the two numbers do not contain any leading zero, except the number 0 itself.
    */
   ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *ptr = l1, *head2 = l2;
        
        while(ptr) {
            
            if(head2) { ptr->val += head2->val; }
            
            if(ptr->val > 9) {
                if(ptr->next) {
                    ptr->next->val++; 
                    ptr->val -= 10;
                }
                else {
                    ListNode *temp = new ListNode(1);
                    ptr->val -= 10;
                    ptr->next = temp;
                }
            }
            
            if(head2) {
                if((ptr->next == nullptr) && head2->next) {
                    ListNode *temp = new ListNode(0);
                    ptr->next = temp;
                }
                head2 = head2->next;
            }
            
            ptr = ptr->next;
        }
        
        return l1;
    }


    /* Flatten a Multilevel Doubly Linked List
    You are given a doubly linked list, which contains nodes that have a next pointer, a previous pointer, and an additional child pointer. This child pointer may or may not point to a separate doubly linked list, also containing these special nodes. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure as shown in the example below.

    Given the head of the first level of the list, flatten the list so that all the nodes appear in a single-level, doubly linked list. Let curr be a node with a child list. The nodes in the child list should appear after curr and before curr.next in the flattened list.

    Return the head of the flattened list. The nodes in the list must have all of their child pointers set to null.
    */
   Node* flatten(Node* head) {
        Node *ptr_flat = head, *ptr_child = nullptr;
        
        while(ptr_flat) {
            if(ptr_flat->child == nullptr) { ptr_flat = ptr_flat->next; }
            
            else {
                ptr_child = ptr_flat->child;
                ptr_child->prev = ptr_flat;
                
                while(ptr_child->next) { ptr_child = ptr_child->next; }
                
                ptr_child->next = ptr_flat->next;
                if(ptr_flat->next) { ptr_flat->next->prev = ptr_child; }
                ptr_flat->next = ptr_flat->child;
                ptr_flat->child = nullptr;
                
                ptr_child = nullptr;
            }
        }
        
        return head;
    }


    /* Copy List with Random Pointer
    A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

    Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

    For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

    Return the head of the copied linked list.
    */
   Node* copyRandomList(Node* head) {
        Node *new_head = nullptr, *ptr_traverse = head, *ptr_traverse_new = nullptr;
        
        if(head == nullptr) { return nullptr; }
        
        // Clone all nodes
        while(ptr_traverse) {
            Node *copy_node = new Node(ptr_traverse->val);
            copy_node->next = ptr_traverse->next;
            ptr_traverse->next = copy_node;
            
            ptr_traverse = ptr_traverse->next->next;
        }
        
        // Define random mappings
        ptr_traverse = head;
        while(ptr_traverse) {
            if(ptr_traverse->random) { ptr_traverse->next->random = ptr_traverse->random->next; }
            ptr_traverse = ptr_traverse->next->next;
        }
        
        // Delete original nodes
        new_head = head->next;
        ptr_traverse_new = new_head;
        ptr_traverse = head;
        while(ptr_traverse_new) {
            ptr_traverse->next = ptr_traverse->next ? ptr_traverse->next->next : nullptr;
            ptr_traverse_new->next = ptr_traverse_new->next ? ptr_traverse_new->next->next : nullptr;
            
            ptr_traverse_new = ptr_traverse_new->next;
            ptr_traverse = ptr_traverse->next;
        }
        
        return new_head;
    }


    /* Rotate List
    Given the head of a linked list, rotate the list to the right by k places.
    */
   ListNode* rotateRight(ListNode* head, int k) {
        ListNode *new_head = head, *ptr_traverse = head;
        int num_nodes = 1, steps = 0;
        
        if(!head) { return nullptr; }
        if((!head->next) || (k == 0)) { return head; }
        
        while(ptr_traverse->next) { 
            ptr_traverse = ptr_traverse->next;
            num_nodes++;
        }
        
        if((k == num_nodes) || (k % num_nodes == 0)) { return head; }
        
        else {
            ptr_traverse->next = head;
            steps = (k < num_nodes) ? (num_nodes - k) : (num_nodes - (k % num_nodes));
            for(int i = 0; i < steps; i++) { ptr_traverse = ptr_traverse->next; }
            new_head = ptr_traverse->next;
            ptr_traverse->next = nullptr;
            return new_head;
        }
    }
};