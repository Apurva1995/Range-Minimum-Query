/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

class LCA
{
    private int noOfNodes;
    private int levels;
    private Map<Integer, List<Integer>> tree;
    private List<Integer> depth;
    private int parents[][];
    
    public LCA(int noOfNodes) {
        
        this.noOfNodes = noOfNodes;
        this.levels = (int)Math.ceil(Math.log(noOfNodes));
        this.tree = new HashMap<>();
        this.depth = new ArrayList<>(Collections.nCopies(noOfNodes+1,0));
        this.parents = new int[noOfNodes+1][this.levels];
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
        addEdge(2,4);
        addEdge(2,5);
        addEdge(2,6);
        addEdge(3,7);
        addEdge(3,8);
    }
    
    
    public void preprocess() {
        
        for(int i=1;i<=noOfNodes;i++) {
            
            for(int j=1;j<levels;j++) {
                
                if(parents[i][j-1] !=  0)
                    parents[i][j] = parents[parents[i][j-1]][j-1];
            }
        }
    }
    
    void dfs(int cur, int prev) 
    { 
        depth.set(cur, depth.get(prev) + 1);
        parents[cur][0] = prev;
        
        for (int i=0; i<tree.get(cur).size(); i++) 
        { 
            if (tree.get(cur).get(i) != prev) 
                dfs(tree.get(cur).get(i), cur); 
        } 
    } 
    
    public int LCASPARSE(int u, int v) {
        
        if(depth.get(u) > depth.get(v)) {
            
            //Swapping u and v
            u = u + v;
            v = u - v;
            u = u - v;
        }
        
        int diffInDepth = depth.get(v) - depth.get(u);
        int diff = 0;
        
        if(diffInDepth != 0)
            diff = (int)Math.ceil(Math.log(diffInDepth));
        
        //Bringing both nodes at same height
        for(int i=diff;i>=0 && diffInDepth > 0;i--) {
            
            
            if((depth.get(v)- depth.get(parents[v][i])) > diffInDepth)
                continue;
            
            else {
                
                diffInDepth -= (depth.get(v) - depth.get(parents[v][i]));
                v = parents[v][i];
            }
        }
        
        if(u == v)
            return u;
        
        for(int i=levels-1;i>=0;i--) {
            
            if(parents[u][i] != parents[v][i]) {
                
                u = parents[u][i];
                v = parents[v][i];
            }
        }
        return parents[u][0];
    }
    
	public static void main (String[] args) throws java.lang.Exception
	{
	    int nodes;
	    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	    
	    System.out.println("Enter number of nodes");
	    nodes = Integer.parseInt(br.readLine());
		LCA lca = new LCA(nodes);
		
		//Creating tree 
		lca.createTree();
		
		//Calling dfs on the tree to find immidiate parent and depth of every node, assuming 1 is the root node
		lca.dfs(1,0);
		
		//Filling 2^i parents of every node
		lca.preprocess();
		
		System.out.println("LCA(6,7) : " + lca.LCASPARSE(3, 7));
	}
}
