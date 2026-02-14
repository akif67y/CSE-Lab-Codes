class Node<T extends Comparable<T>> {
    T value;
    Node<T> left, right, parent;
    boolean red; 
    int size;      
    Node(T value) {
        this.value = value;
        this.red = true; 
        this.size = 1;
        this.left = null;
        this.right = null;
        this.parent = null;
    }
}
public class RedBlackTree<T extends Comparable<T>> {
    private Node<T> root;
    private Node<T> leafBlack; 

    public RedBlackTree() {
        leafBlack = new Node<>(null);
        leafBlack.red = false;
        leafBlack.size = 0;
        root = leafBlack;
    }


    public boolean insert(T value) {
        if (search(value)) return false; 
        
        Node<T> node = new Node<>(value);
        node.left = leafBlack;
        node.right = leafBlack;
        Node<T> y = null;
        Node<T> x = root;

        while (x != leafBlack) {
            y = x;
            x.size++;
            if (node.value.compareTo(x.value) < 0) {
                x = x.left;
            } else {
                x = x.right;
            }
        }
        node.parent = y;
        if (y == null) {
            root = node;
        } else if (node.value.compareTo(y.value) < 0) {
            y.left = node;
        } else {
            y.right = node;
        }

        if (node.parent == null) {
            node.red = false;
            return true;
        }

        if (node.parent.parent == null) {
            return true;
        }

        fixInsert(node);
        return true;
    }

    public boolean delete(T key) {
        Node<T> z = searchNode(key);
        if (z == leafBlack) return false; 
        deleteNodeHelper(z);
        return true;
    }
    public boolean search(T value) {
        return searchNode(value) != leafBlack;
    }
    public int countLessThan(T value) {
        return countLessThanRecursive(root, value);
    }
    private int countLessThanRecursive(Node<T> node, T value) {
        if (node == leafBlack) return 0;

        int cmp = value.compareTo(node.value);

        if (cmp < 0) {
            return countLessThanRecursive(node.left, value);
        } else if (cmp > 0) {
            return node.left.size + 1 + countLessThanRecursive(node.right, value);
        } else {
            return node.left.size;
        }
    }
    private Node<T> searchNode(T value) {
        Node<T> current = root;
        while (current != leafBlack) {
            if (value.equals(current.value)) {
                return current;
            } else if (value.compareTo(current.value) < 0) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        return leafBlack;
    }
    private void decrementSizeUpwards(Node<T> node) {
        while (node != null && node != leafBlack) {
            node.size--;
            node = node.parent;
        }
    }
    private void updateSize(Node<T> node) {
        if (node != leafBlack) {
            node.size = node.left.size + node.right.size + 1;
        }
    }

    private void leftRotate(Node<T> x) {
        Node<T> y = x.right;
        x.right = y.left;
        if (y.left != leafBlack) {
            y.left.parent = x;
        }
        y.parent = x.parent;
        if (x.parent == null) {
            root = y;
        } else if (x == x.parent.left) {
            x.parent.left = y;
        } else {
            x.parent.right = y;
        }
        y.left = x;
        x.parent = y;

        // Update sizes: x is now child of y, so update x first, then y
        y.size = x.size; // y takes x's place, so it takes x's old size
        updateSize(x);   // x is now a child, recalculate its size
    }

    private void rightRotate(Node<T> x) {
        Node<T> y = x.left;
        x.left = y.right;
        if (y.right != leafBlack) {
            y.right.parent = x;
        }
        y.parent = x.parent;
        if (x.parent == null) {
            root = y;
        } else if (x == x.parent.right) {
            x.parent.right = y;
        } else {
            x.parent.left = y;
        }
        y.right = x;
        x.parent = y;
        y.size = x.size;
        updateSize(x);
    }

    private void fixInsert(Node<T> k) {
        Node<T> u;
        while (k.parent.red) {
            if (k.parent == k.parent.parent.right) { // inserted in the right side
                u = k.parent.parent.left;
                if (u.red) {
                    u.red = false;
                    k.parent.red = false;
                    k.parent.parent.red = true;
                    k = k.parent.parent;
                } else {
                    if (k == k.parent.left) {
                        k = k.parent;
                        rightRotate(k);
                    }
                    k.parent.red = false;
                    k.parent.parent.red = true;
                    leftRotate(k.parent.parent);
                }
            } else { //inserted in the left side
                u = k.parent.parent.right; //uncle
                if (u.red) { //red-red(recolor and move up)
                    u.red = false;
                    k.parent.red = false;
                    k.parent.parent.red = true;
                    k = k.parent.parent;
                } else { //red-black(two case, one include extra left rotation)
                    if (k == k.parent.right) {
                        k = k.parent; // we changing K to be A now, it helps us dui dhil e ek pakhi
                        leftRotate(k); 
                    }
                    k.parent.red = false;
                    k.parent.parent.red = true; 
                    rightRotate(k.parent.parent);
                }
            }
            if (k == root) break;
        }
        root.red = false;
    }

    private void transplant(Node<T> u, Node<T> v) {
        if (u.parent == null) {
            root = v;
        } else if (u == u.parent.left) {
            u.parent.left = v;
        } else {
            u.parent.right = v;
        }
        v.parent = u.parent;
    }

    private void deleteNodeHelper(Node<T> z) {
        
        Node<T> x, y;
        y = z;
        boolean yOriginalColor = y.red;

        if (z.left == leafBlack) {
            x = z.right;
            transplant(z, z.right);
            decrementSizeUpwards(z.parent); 
        } else if (z.right == leafBlack) {
            x = z.left;
            transplant(z, z.left);
            decrementSizeUpwards(z.parent);
        } else {
    y = minimum(z.right);
    yOriginalColor = y.red;
    x = y.right;
    decrementSizeUpwards(y.parent); 
    if (y.parent == z) {
        x.parent = y; 
        
    } else {
        transplant(y, y.right);
        y.right = z.right;
        y.right.parent = y;
        
    }

    transplant(z, y);
    y.left = z.left;
    y.left.parent = y;
    y.red = z.red;
    y.size = z.size; 
    }
        
        if (!yOriginalColor) {
            fixDelete(x);
        }
    }

    private void fixDelete(Node<T> x) {
        while (x != root && !x.red) {
            if (x == x.parent.left) {
                Node<T> w = x.parent.right; //uncle
                if (w.red) { //case 3
                    w.red = false;
                    x.parent.red = true;
                    leftRotate(x.parent);
                    w = x.parent.right; //new uncle
                }
                if (!w.left.red && !w.right.red) { // both nephew black , case 4.3
                    w.red = true;
                    x = x.parent; //take the violation to the parent level
                } else {
                    if (!w.right.red) { //right nephew black
                        w.left.red = false;
                        w.red = true;
                        rightRotate(w);
                        w = x.parent.right; // now we take this to the phase where right nephew red
                    }
                    w.red = x.parent.red;
                    x.parent.red = false;
                    w.right.red = false;
                    leftRotate(x.parent);
                    x = root;
                }
            } else {
                Node<T> w = x.parent.left;
                if (w.red) {
                    w.red = false;
                    x.parent.red = true;
                    rightRotate(x.parent);
                    w = x.parent.left;
                }
                if (!w.right.red && !w.left.red) {
                    w.red = true;
                    x = x.parent;
                } else {
                    if (!w.left.red) {
                        w.right.red = false;
                        w.red = true;
                        leftRotate(w);
                        w = x.parent.left;
                    }
                    w.red = x.parent.red;
                    x.parent.red = false;
                    w.left.red = false;
                    rightRotate(x.parent);
                    x = root;
                }
            }
        }
        x.red = false;
    }

    private Node<T> minimum(Node<T> node) {
        while (node.left != leafBlack) {
            node = node.left;
        }
        return node;
    }
}
