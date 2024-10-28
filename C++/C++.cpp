#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    string multiply(string num1, string num2) {
        Node* result = multiplyStrings(num1, num2);
        result = reverseList(result);
        return linkedListToString(result);
    }

private:
    Node* multiplyStrings(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return new Node(0);

        Node* result = nullptr;
        int len1 = num1.size(), len2 = num2.size();

        for (int i = len1 - 1; i >= 0; --i) {
            Node* tempResult = nullptr;
            int carry = 0;
            int n1 = num1[i] - '0';

            // Thêm số 0 vào cuối để căn chỉnh
            for (int k = 0; k < len1 - 1 - i; ++k) {
                tempResult = addTail(tempResult, 0);
            }

            for (int j = len2 - 1; j >= 0; --j) {
                int n2 = num2[j] - '0';
                int product = n1 * n2 + carry;
                carry = product / 10;
                tempResult = addTail(tempResult, product % 10);
            }

            if (carry > 0) {
                tempResult = addTail(tempResult, carry);
            }

            result = addLists(result, tempResult);
        }

        return result;
    }

    Node* addTail(Node* head, int val) {
        if (!head) return new Node(val);
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new Node(val);
        return head;
    }

    Node* addLists(Node* list1, Node* list2) {
        Node* result = nullptr;
        int carry = 0;

        while (list1 || list2 || carry) {
            int sum = carry;
            if (list1) {
                sum += list1->data;
                list1 = list1->next;
            }
            if (list2) {
                sum += list2->data;
                list2 = list2->next;
            }
            carry = sum / 10;
            result = addTail(result, sum % 10);
        }

        return result;
    }

    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
    }

    string linkedListToString(Node* head) {
        string result;
        while (head) {
            result += to_string(head->data);
            head = head->next;
        }
        return result;
    }
};
