import java.util.*;
class Node<T extends Comparable<T>> {
    T value;
    Node<T> left;
    Node<T> right;
    int height;

    Node(T value) {
        this.value = value;
        this.height = 1; 
    }
}

public class AVLTree<T extends Comparable<T>> {
    
    private Node<T> root;

    public boolean insert(T value) {
        if (search(value)) return false; 
        root = insertRecursive(root, value);
        return true;
    }

    public boolean delete(T value) {
        if (!search(value)) return false; 
        root = deleteRecursive(root, value);
        return true;
    }

    public boolean search(T value) {
        return searchRecursive(root, value);
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

    private boolean searchRecursive(Node<T> node, T value){
        if (node == null) return false;
        
        int cmp = value.compareTo(node.value);
        if (cmp < 0) return searchRecursive(node.left, value);
        else if (cmp > 0) return searchRecursive(node.right, value);
        else return true; 
    }

  private Node<T> insertRecursive(Node<T> node, T value) {
        if (node == null) return new Node<>(value);

        int cmp = value.compareTo(node.value);
        if (cmp < 0)
            node.left = insertRecursive(node.left, value);
        else if (cmp > 0)
            node.right = insertRecursive(node.right, value);
        else 
            return node;
        updateHeight(node);
        return balanceNode(node); 
    }
    
  private Node<T> balanceNode(Node<T> node) {
        int balance = getBalance(node);
        if (balance > 1) {
            if (getBalance(node.left) >= 0) {
                return rightRotate(node);
            } 
            else {
                node.left = leftRotate(node.left);
                return rightRotate(node);
            }
        }
        if (balance < -1) {

            if (getBalance(node.right) <= 0) {
                return leftRotate(node);
            } 
            else {
                node.right = rightRotate(node.right);
                return leftRotate(node);
            }
        }
        return node;
    }

    private Node<T> deleteRecursive(Node<T> node, T value) {
        if (node == null) return node;
        int cmp = value.compareTo(node.value);
        if (cmp < 0) {
            node.left = deleteRecursive(node.left, value);
        } else if (cmp > 0) {
            node.right = deleteRecursive(node.right, value);
        } else {
            if ((node.left == null) || (node.right == null)) {
                Node<T> temp = (node.left != null) ? node.left : node.right;
                if (temp == null) {
                    node = null;
                } else { 
                    node = temp; 
                }
            } else {
                Node<T> temp = minValueNode(node.right);
                node.value = temp.value;
                node.right = deleteRecursive(node.right, temp.value);
            }
        }
        if (node == null) return null;
        updateHeight(node);
        return balanceNode(node);
    }
    private Node<T> rightRotate(Node<T> y) {
        Node<T> x = y.left;
        Node<T> T2 = x.right;
        x.right = y;
        y.left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    private Node<T> leftRotate(Node<T> x) {
        Node<T> y = x.right;
        Node<T> T2 = y.left;
        y.left = x;
        x.right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }
    private int getHeight(Node<T> n) {
        return (n == null) ? 0 : n.height;
    }

    private void updateHeight(Node<T> n) {
        n.height = Math.max(getHeight(n.left), getHeight(n.right)) + 1;
    }

    private int getBalance(Node<T> n) {
        return (n == null) ? 0 : getHeight(n.left) - getHeight(n.right);
    }

    private Node<T> minValueNode(Node<T> node) {
        Node<T> current = node;
        while (current.left != null)
            current = current.left;
        return current;
    }
   private void preOrder(Node<T> node, StringBuilder sb) {
        if (node != null) {
            sb.append(node.value).append(" ");
            preOrder(node.left, sb);
            preOrder(node.right, sb);
        }
    }

    private void inOrder(Node<T> node, StringBuilder sb) {
        if (node != null) {
            inOrder(node.left, sb);
            sb.append(node.value).append(" ");
            inOrder(node.right, sb);
        }
    }

    private void postOrder(Node<T> node, StringBuilder sb) {
        if (node != null) {
            postOrder(node.left, sb);
            postOrder(node.right, sb);
            sb.append(node.value).append(" ");
        }
    }

    private void levelOrder(Node<T> root, StringBuilder sb) {
        if (root == null) return;
        Queue<Node<T>> queue = new LinkedList<>();
        queue.add(root);
        while (!queue.isEmpty()) {
            Node<T> current = queue.poll();
            sb.append(current.value).append(" ");
            if (current.left != null) queue.add(current.left);
            if (current.right != null) queue.add(current.right);
        }
    }
}