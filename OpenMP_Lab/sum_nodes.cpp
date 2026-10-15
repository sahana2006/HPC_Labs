
#include <iostream>
#include <omp.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Create a sample binary tree
Node* createTree() {
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(20);

    root->left->left = new Node(3);
    root->left->right = new Node(7);

    root->right->left = new Node(15);
    root->right->right = new Node(25);

    return root;
}

// Parallel sum using OpenMP tasks
long long parallelSum(Node* root) {
    if (root == nullptr)
        return 0;

    long long leftSum = 0;
    long long rightSum = 0;

    #pragma omp task shared(leftSum) 
    {
        if(root->left != nullptr)
        {
            leftSum = parallelSum(root->left);
        }
    }

    #pragma omp task shared(rightSum) 
    {
        if(root->right != nullptr)
        {
            rightSum = parallelSum(root->right);
        }
    }
    #pragma omp taskwait // Ensures that the child tasks finsh faster before the parent node combines the result

    return root->data + leftSum + rightSum;
}


int main() {
    Node* root = createTree();
    long long sum = 0;

    omp_set_dynamic(0);
    omp_set_num_threads(4);

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "Number of threads = "
                 << omp_get_num_threads() << '\n';

            sum = parallelSum(root);
        }
    }

    double end = omp_get_wtime();

    cout << "Sum of all node values = " << sum << '\n';
    cout << "Execution time = " << end - start << " seconds\n";

    return 0;
}

