/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

class LCA
{
    private Map<Integer, List<Integer>> tree;
    private List<Integer> depth;
    private List<Integer> parent;
    private List<Integer> visited;
    private List<Integer> jumpParent;
    private int blockSize;
    
    public LCA() {
        
        tree = new HashMap<>();
        depth = new ArrayList<>(Collections.nCopies(16, 0));
        parent = new ArrayList<>(Collections.nCopies(16, 0));
        //Assuming the number of vertices are 15
        visited = new ArrayList<>(Collections.nCopies(16, 0));
        jumpParent = new ArrayList<>(Collections.nCopies(16, 0));
    }
    
    public void addEdge(int u, int v) {
        
        if(tree.get(u) == null) {
            
            tree.put(u, new ArrayList<Integer>());
        }
        
        if(tree.get(v) == null) {
            
            tree.put(v, new ArrayList<Integer>());
        }
        
        tree.get(u).add(v);
        tree.get(v).add(u);
    }
    
    public void createTree() {
        
        // adding edges to the tree
        addEdge(1,2);
        addEdge(1,3);
        addEdge(1,4);
        addEdge(2,5);
        addEdge(2,6);
        addEdge(3,7);
        addEdge(4,8);
        addEdge(4,9);
        addEdge(9,10);
        addEdge(9,11);
        addEdge(7,12);
        addEdge(7,13);
        addEdge(10,14);
        addEdge(14,15);
    }
    
    private void dfs(int par, int chi, int dep) {
        
        parent.set(chi, par);
        visited.set(chi, 1);
        depth.set(chi, dep);
        
        if(parent.get(chi) == -1)
            jumpParent.set(chi, 0);
        else {
            
            if(depth.get(chi)/blockSize == depth.get(par)/blockSize)
                jumpParent.set(chi, jumpParent.get(par));
            else    
                jumpParent.set(chi, par);
        }
        
        for(int i=0;i < tree.get(chi).size();i++) {
            
            if(visited.get(tree.get(chi).get(i)) == 0)
                dfs(chi, tree.get(chi).get(i), dep+1);
        }
    }
    
    public void preprocess(double height) {
        
        blockSize = (int) Math.sqrt(height);
        dfs(-1, 1, 0);
    }
    
    int LCANaive(int u, int v) {
        
        while(u != v){
            
            if(depth.get(u) > depth.get(v)) {
                
                //Swapping u and v
                u = u + v;
                v = u - v;
                u = u - v;
            }
            v = parent.get(v);
        }
        
        return u;    
    }
    
    int LCASQRT(int u, int v) {
        
        while(jumpParent.get(u) != jumpParent.get(v)) {
            
            if(depth.get(u) > depth.get(v)) {
                
                //Swapping u and v
                u = u + v;
                v = u - v;
                u = u - v;
            }
            v = jumpParent.get(v);    
        }
        return LCANaive(u, v);
    }
    
	public static void main (String[] args) throws java.lang.Exception
	{
		LCA lca = new LCA();
		
		lca.createTree();
		//Providing the height manually for the tree
		lca.preprocess(5.0);
		System.out.println("LCA(11,8) : " + lca.LCASQRT(15, 1));
		System.out.println("LCA(3,13) : " + lca.LCASQRT(3, 13));
	}
}
