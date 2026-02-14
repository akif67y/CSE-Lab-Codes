import java.util.*;

// Node now holds a Key and a Value
class Node<K extends Comparable<K>, V> {
    K key;
    V value;
    Node<K, V> left;
    Node<K, V> right;
    int height;

    Node(K key, V value) {
        this.key = key;
        this.value = value;
        this.height = 1;
    }
}

public class AVLTree<K extends Comparable<K>, V> {

    private Node<K, V> root;

    // Insert now takes a Key and a Value
    public boolean insert(K key, V value) {
        if (search(key)) return false; // Duplicate keys not allowed
        root = insertRecursive(root, key, value);
        return true;
    }

    // Delete is based on the Key
    public boolean delete(K key) {
        if (!search(key)) return false;
        root = deleteRecursive(root, key);
        return true;
    }

    // Search checks for the existence of a Key
    public boolean search(K key) {
        return searchRecursive(root, key);
    }
    
    // Helper to retrieve a value (typical dictionary/map behavior)
    public V get(K key) {
        Node<K, V> node = getNodeRecursive(root, key);
        return (node != null) ? node.value : null;
    }

    public String getTraversal(int type) {
        if (root == null) return "";
        StringBuilder sb = new StringBuilder();

        switch (type) {
            case 1: preOrder(root, sb); break;
            case 2: inOrder(root, sb); break;
            case 3: postOrder(root, sb); break;
            case 4: levelOrder(root, sb); break;
        }

        return sb.toString().trim();
    }

    // --- Recursive Helpers ---

    private boolean searchRecursive(Node<K, V> node, K key) {
        if (node == null) return false;
        int cmp = key.compareTo(node.key);
        if (cmp < 0) return searchRecursive(node.left, key);
        else if (cmp > 0) return searchRecursive(node.right, key);
        else return true;
    }
    
    private Node<K, V> getNodeRecursive(Node<K, V> node, K key) {
        if (node == null) return null;
        int cmp = key.compareTo(node.key);
        if (cmp < 0) return getNodeRecursive(node.left, key);
        else if (cmp > 0) return getNodeRecursive(node.right, key);
        else return node;
    }

    private Node<K, V> insertRecursive(Node<K, V> node, K key, V value) {
        // 1. Perform standard BST insert
        if (node == null) return new Node<>(key, value);

        int cmp = key.compareTo(node.key);
        if (cmp < 0)
            node.left = insertRecursive(node.left, key, value);
        else if (cmp > 0)
            node.right = insertRecursive(node.right, key, value);
        else
            return node; // Duplicate keys not allowed in this implementation

        // 2. Update height
        updateHeight(node);

        // 3. Balance the node
        return balanceNode(node);
    }

    private Node<K, V> deleteRecursive(Node<K, V> node, K key) {
        if (node == null) return node;

        int cmp = key.compareTo(node.key);
        if (cmp < 0) {
            node.left = deleteRecursive(node.left, key);
        } else if (cmp > 0) {
            node.right = deleteRecursive(node.right, key);
        } else {
            // Node with only one child or no child
            if ((node.left == null) || (node.right == null)) {
                Node<K, V> temp = (node.left != null) ? node.left : node.right;
                if (temp == null) {
                    node = null;
                } else {
                    node = temp;
                }
            } else {
                // Node with two children: Get inorder successor (smallest in right subtree)
                Node<K, V> temp = minValueNode(node.right);
                
                // Copy the inorder successor's data to this node
                node.key = temp.key;
                node.value = temp.value; 

                // Delete the inorder successor
                node.right = deleteRecursive(node.right, temp.key);
            }
        }

        if (node == null) return null;

        updateHeight(node);
        return balanceNode(node);
    }

    private Node<K, V> balanceNode(Node<K, V> node) {
        int balance = getBalance(node);

        // Left Heavy
        if (balance > 1) {
            if (getBalance(node.left) >= 0) {
                return rightRotate(node);
            } else {
                node.left = leftRotate(node.left);
                return rightRotate(node);
            }
        }

        // Right Heavy
        if (balance < -1) {
            if (getBalance(node.right) <= 0) {
                return leftRotate(node);
            } else {
                node.right = rightRotate(node.right);
                return leftRotate(node);
            }
        }
        return node;
    }

    // --- Rotations & Utilities ---

    private Node<K, V> rightRotate(Node<K, V> y) {
        Node<K, V> x = y.left;
        Node<K, V> T2 = x.right;

        // Perform rotation
        x.right = y;
        y.left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    private Node<K, V> leftRotate(Node<K, V> x) {
        Node<K, V> y = x.right;
        Node<K, V> T2 = y.left;

        // Perform rotation
        y.left = x;
        x.right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    private int getHeight(Node<K, V> n) {
        return (n == null) ? 0 : n.height;
    }

    private void updateHeight(Node<K, V> n) {
        n.height = Math.max(getHeight(n.left), getHeight(n.right)) + 1;
    }

    private int getBalance(Node<K, V> n) {
        return (n == null) ? 0 : getHeight(n.left) - getHeight(n.right);
    }

    private Node<K, V> minValueNode(Node<K, V> node) {
        Node<K, V> current = node;
        while (current.left != null)
            current = current.left;
        return current;
    }

    // --- Traversals (Printing Key:Value) ---

    private void preOrder(Node<K, V> node, StringBuilder sb) {
        if (node != null) {
            sb.append(node.value).append(" ");
            preOrder(node.left, sb);
            preOrder(node.right, sb);
        }
    }

    private void inOrder(Node<K, V> node, StringBuilder sb) {
        if (node != null) {
            inOrder(node.left, sb);
           sb.append(node.value).append(" ");
            inOrder(node.right, sb);
        }
    }

    private void postOrder(Node<K, V> node, StringBuilder sb) {
        if (node != null) {
            postOrder(node.left, sb);
            postOrder(node.right, sb);
        sb.append(node.value).append(" ");
        }
    }

    private void levelOrder(Node<K, V> root, StringBuilder sb) {
        if (root == null) return;
        Queue<Node<K, V>> queue = new LinkedList<>();
        queue.add(root);
        while (!queue.isEmpty()) {
            Node<K, V> current = queue.poll();
            sb.append(current.value).append(" ");
            if (current.left != null) queue.add(current.left);
            if (current.right != null) queue.add(current.right);
        }
    }
    
   
}