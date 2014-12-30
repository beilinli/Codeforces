import java.io.*;
import java.util.ArrayList;

/*
 * My solution to Codeforces Good Bye 2014 contest, problem D.
 * Problem link: http://codeforces.com/contest/500/problem/D
 * @author Beilin Li
 */

public class D500 {
	static ArrayList<int[]> adjList[];
	static int n, size[], pairDist[];
	
	@SuppressWarnings("unchecked") // ArrayList[] declaration below
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		n = pi(rl(in));
		
		adjList = new ArrayList[n + 2];
		for (int i = 0; i <= n; i++) adjList[i] = new ArrayList<int[]>();
		size = new int[n + 2];
		pairDist = new int[n + 2];
		
		int road[][] = new int[n - 1][3];
		
		for (int i = 0; i + 1 < n; i++) {
			String[] roadIn = rl(in).split(" ");
			int a = pi(roadIn[0]), b = pi(roadIn[1]), d = pi(roadIn[2]);
			adjList[a].add(new int[]{b, d});
			adjList[b].add(new int[]{a, d});
			
			road[i][0] = a;
			road[i][1] = b;
			road[i][2] = d;
		}
		
		calcTotalSize(1, -1);
		long totalDist = 0;
		for (int i = 0; i < road.length; i++) {
			int s = Math.min(size[road[i][0]], size[road[i][1]]);
			totalDist += 1L * s * (n - s) * road[i][2];
		}
		
		int q = pi(rl(in));
		for (int i = 0; i < q; i++) {
			String[] query = rl(in).split(" ");
			int k = pi(query[0]) - 1, w = pi(query[1]);
			int s = Math.min(size[road[k][0]], size[road[k][1]]);
			
			totalDist -=  1L * s * (n - s) * (road[k][2] - w);
			road[k][2] = w;
			System.out.println(6.0 * totalDist / n / (n - 1));
		}
	}
	
	static int calcTotalSize(int v, int prev) {
		if (size[v] != 0) return size[v];
		size[v] = 1;
		for (int[] vd : adjList[v]) {
			if (vd[0] != prev)
				size[v] += calcTotalSize(vd[0], v);
		}
		
		return size[v];
	}
	
	/* wrapper functions to make reading input less tedious */
	static int pi(String s) { return Integer.parseInt(s); }
	static String rl(BufferedReader br) throws IOException { return br.readLine(); }
}