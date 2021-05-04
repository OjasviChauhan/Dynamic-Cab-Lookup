//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;
#define endl '\n'

const int k = 2;

class node {
public:
	int point[k]; // To store k dimensional point
	node* left;
	node* right;

	// constructor to create a node of KD tree
	node(int arr[]) {
		for (int i = 0; i < k; i++) {
			point[i] = arr[i];
		}
		left = NULL;
		right = NULL;
	}
};

void print(node* root) {
	if (root == NULL) {
		return;
	}
	cout << endl;
	for (int i = 0; i < k; i++)
		cout << root->point[i] << ",";
	cout << endl;
	print(root->left);
	print(root->right);
}

void Alert() {
	cout << endl;
	cout << "No cabs are available at the moment" << endl;
	cout << endl;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
node* insert(node* root, int point[], unsigned depth) {
	// Tree is empty?
	if (root == NULL)
		return new node(point);

	// Calculate current dimension (cd) of comparison
	unsigned cd = depth % k;

	// Compare the new point with root on current dimension 'cd'
	// and decide the left or right subtree
	if (point[cd] < (root->point[cd]))
		root->left  = insert(root->left, point, depth + 1);
	else
		root->right = insert(root->right, point, depth + 1);

	return root;
}

bool isInsideRect(int x1, int y1, int x2, int y2, int x, int y) {
	if (x > x1 and x < x2 and y > y1 and y < y2)
		return true;
	return false;
}

void rangeSearch2D(node* root, unsigned depth, int rectangle[][2], vector<pair<int, int>> &count) {
	if (root == NULL) {
		//cout<<"hit base case"<<endl;
		return;
	}
	//cout<<root->point[0]<<","<<root->point[1]<<endl;

	unsigned cd = depth % k;
	int x = root->point[0];
	int y = root->point[1];
	int recX1 = rectangle[0][0];
	int recY1 = rectangle[0][1];
	int recX2 = rectangle[1][0];
	int recY2 = rectangle[1][1];

	// plain is getting divided vertically
	if (cd == 0) {
		// rectangle is on the left side of dividing line
		if (x > recX1 and x > recX2) {
			//cout<<"rectangle is on the left side"<<endl;
			rangeSearch2D(root->left, depth + 1, rectangle, count);
		}
		// rectangle is on the right side of dividing line
		else if (x < recX1 and x < recX2) {
			//cout<<"rectangle is on the right side"<<endl;
			rangeSearch2D(root->right, depth + 1, rectangle, count);
		}
		// dividing line is intersecting the rectangle
		else if (x >= recX1 and x <= recX2) {
			//cout<<"vertically intersecting"<<endl;

			if (isInsideRect(recX1, recY1, recX2, recY2, x, y))
				count.push_back({x, y});

			rangeSearch2D(root->left, depth + 1, rectangle, count);
			rangeSearch2D(root->right, depth + 1, rectangle, count);
		}
	}

	// plain is dividing horizontally
	else {
		// rectangle is below
		if (y > recY1 and y > recY2) {
			//cout<<"rectangle is below"<<endl;
			rangeSearch2D(root->left, depth + 1, rectangle, count);
		}
		// rectangle is above
		else if (y < recY1 and y < recY2) {
			//cout<<"rectangle is above"<<endl;
			rangeSearch2D(root->right, depth + 1, rectangle, count);
		}
		// dividing line is intersecting the rectangle
		else if (y >= recY1 and y <= recY2) {
			//cout<<"horizontally intersecting"<<endl;

			if (isInsideRect(recX1, recY1, recX2, recY2, x, y))
				count.push_back({x, y});

			rangeSearch2D(root->left, depth + 1, rectangle, count);
			rangeSearch2D(root->right, depth + 1, rectangle, count);
		}
	}
}

double dist(int point[], int p[]) {
	int x1 = point[0];
	int y1 = point[1];
	int x2 = p[0];
	int y2 = p[1];
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

node* nearestNeighbourSearch(node* current, int p[], node* nearest, double &closest) {
	if (current == NULL) {
		//cout<<"hit base case"<<endl;
		closest = dist(nearest->point, p);
		return nearest;
	}

	if (dist(current->point, p) < dist(nearest->point, p)) {
		//cout<<"node is farther than current nearest"<<endl;
		nearest = current;
	}

	node* left = nearestNeighbourSearch(current->left, p, nearest, closest);
	if (dist(left->point, p) < dist(nearest->point, p)) {
		//cout<<"new champion: "<<left->point[0]<<","<<left->point[1]<<endl;
		nearest = left;
	}

	node* right = nearestNeighbourSearch(current->right, p, nearest, closest);
	if (dist(right->point, p) < dist(nearest->point, p)) {
		//cout<<"new champion: "<<right->point[0]<<","<<right->point[1]<<endl;
		nearest = right;
	}

	return nearest;
}


void option1(node* root, int points[][k]) {

	cout << "Enter the coordinates of rectangle: " << endl;
	cout << "Left Bottom: ";
	int rectangle[2][2];
	int x1, y1, x2, y2;
	cin >> x1 >> y1;
	rectangle[0][0] = x1;
	rectangle[0][1] = y1;
	cout << "Top Right: ";
	cin >> x2 >> y2;
	rectangle[1][0] = x2;
	rectangle[1][1] = y2;

	vector<pair<int, int>> count;
	rangeSearch2D(root, 0, rectangle, count);

	if (count.empty()) {
		cout << "There are no cabs inside the Rectangle" << endl;
		cout << endl;
	}
	else {
		cout << "Points inside the rectangle are: " << endl;
		for (auto p : count) {
			cout << "(" << p.first << "," << p.second << ")" << endl;
		}
		cout << endl;
	}
}

void option2(node* root, int points[][k]) {

	double closest = INT_MAX;
	cout << "Enter the query point" << endl;
	int p[k];
	for (int i = 0; i < k; i++) {
		cin >> p[i];
	}
	node* ans = nearestNeighbourSearch(root, p, root, closest);

	cout << "The closest cab is present at: " << ans->point[0] << "," << ans->point[1] << " having "
	     << closest << " units distance from you." << endl;

	cout << endl;
}

int main() {

	cout << "Welcome to DYNAMIC CAB LOOKUP" << endl;
	cout << endl;

	cout << "How many cabs are there ?" << endl;
	int c;
	cin >> c;
	cout << endl;
	int points[c][k];

	if (c != 0) {
		cout << "Enter the coordinates of all cabs present in the town" << endl;
		for (int i = 0; i < c; i++) {
			int x, y;
			cin >> x >> y;
			points[i][0] = x;
			points[i][1] = y;
		}
	}
	int n = sizeof(points) / sizeof(points[0]);

	cout << endl;
	cout << "Inserting all cab's data..." << endl;
	cout << endl;

	node* root = NULL;
	for (int i = 0; i < n; i++)
		root = insert(root, points[i], 0);

	cout << "All data inserted Successfully!!" << endl;
	cout << endl;

	while (true) {
		cout << "1. Perform Rectangular Search" << endl;
		cout << "2. Perform Nearest Neighbour Search" << endl;
		cout << "3. View all data" << endl;
		cout << "4. Exit" << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1: root == NULL ? Alert() : option1(root, points);
			break;

		case 2: root == NULL ? Alert() : option2(root, points);
			break;

		case 3: root == NULL ? Alert() : print(root);
			break;

		case 4: exit(0);

		default : cout << "Invalid Choice" << endl;
		}
	}

	return 0;
}


/*

3 6
17 15
13 15
6 12
9 1
2 7
10 19

*/