#include "RBtree.h"

using namespace std;

void InsertNode(Node*& root, int value) {

	Node* nodetmp = root;

	//����� ����� ��� ������� ������ ���� �� ������ ��� ��������
	while (true) {						
		if (value < nodetmp->value) {

			if (nodetmp->left == nullptr) {
				nodetmp->left = new Node{ value, nodetmp, nullptr, nullptr, 1 };
				InsertFix(nodetmp->left, root);
				return;
			}
			nodetmp = nodetmp->left;
		}

		else if (value > nodetmp->value) {

			if (nodetmp->right == nullptr) {
				nodetmp->right = new Node{ value, nodetmp, nullptr, nullptr, 1 };
				InsertFix(nodetmp->right, root);
				return;
			}
			nodetmp = nodetmp->right;
		}
		else {
			cout << "���� � ����� ��������� ��� ����������!";
			return;
		}
	}
}

void InsertFix(Node* node, Node*& root) {
	while (node->parent->Red) {
		//���� �������� - ����� �������
		if (node->parent == node->parent->parent->left) {
			//��������� ���������� �� ������ �������
			if (node->parent->parent->right != nullptr) {
				//���� ������ ������� ����������, �� ���������: ������� �� ��?
				if (node->parent->parent->right->Red) {
					node->parent->Red = 0;
					node->parent->parent->right->Red = 0;
					node->parent->parent->Red = 1;
					node = node->parent->parent;
				}
				else
					//���� ������ ������� ������, ���������� ��������� ������� ��� ���� ���
					goto p1;
			}
			else {
			p1:
				//���� ���� ��������� ������ �� ���� �� ����������� �������
				if (node == node->parent->right) {
					LeftRotate(root, node->parent->value);
					node = node->left;
				}
				RightRotate(root, node->parent->parent->value);
				node->parent->right->Red = 1;
				node->parent->Red = 0;
				node = node->parent;
			}
		}

		/*���� ���� - ������ �������*/
		else {

			//��������� ���������� �� ����� �������
			if (node->parent->parent->left != nullptr) {
				if (node->parent->parent->left->Red) {
					node->parent->Red = 0;
					node->parent->parent->left->Red = 0;
					node->parent->parent->Red = 1;
					node = node->parent->parent;
				}
				else
					//���� ����� ������� ������, ���������� ��������� ������� ��� ���� ���
					goto p2;
			}
			else {

			p2:
				//���� ���� ��������� ����� �� ���� �� ����������� �������
				if (node == node->parent->left) {
					RightRotate(root, node->parent->value);
					node = node->right;
				}
				LeftRotate(root, node->parent->parent->value);
				node->parent->left->Red = 1;
				node->parent->Red = 0;
				node = node->parent;
			}
		}
		//��������� ������ ������ � ����� ������
		root->Red = 0;

		//��������� ���� ���� ��� �������� ������ nullptr
		if (node->parent == nullptr)
			break;
	}
}

void DeleteNode(Node*& root, int value) {
	Node* node = root;

	while (node != nullptr)
		if (value < node->value)
			node = node->left;
		else if (value > node->value)
			node = node->right;
		else
			break;

	if (node == nullptr) {
		cout << "��� ������� � ����� ���������!";
		return;
	}

	Delete(root, node);
}

void Delete(Node*& root, Node* node) {

	//�������� ������� ������� ��� ��������
	if (node->Red && node->left == nullptr && node->right == nullptr) {
		ClearNode(node);
	}
	//�������� ������� � ������ ��������
	else if (node->right != nullptr) {
		Node* nodetmp = node->right;

		while (nodetmp->left != nullptr)
			nodetmp = nodetmp->left;

		int tmp = nodetmp->value;
		nodetmp->value = node->value;
		node->value = tmp;

		Delete(root, nodetmp);
	}
	//�������� ������� � ����� ��������
	else if (node->left != nullptr) {
		Node* nodetmp = node->left;

		while (nodetmp->right != nullptr)
			nodetmp = nodetmp->right;

		int tmp = nodetmp->value;
		nodetmp->value = node->value;
		node->value = tmp;

		Delete(root, nodetmp);
	}

	//�������� ������ ������� ��� ��������
	else if (!node->Red && node->left == nullptr && node->right == nullptr) {

		//���� �������� ������� - �������
		if (node->parent->Red) {
			//���� ���� - ������ �������
			if (node == node->parent->right) {
				//���� � "�����" ���� ���� ���� �� ���� ������� ������� ����� ��� ������
				if (node->parent->left->right != nullptr && node->parent->left->right->Red) {
					LeftRotate(root, node->parent->left->value);
					RightRotate(root, node->parent->value);

					node->parent->Red = 0;

					ClearNode(node);
				}
				else if (node->parent->left->left != nullptr && node->parent->left->left->Red) {
					RightRotate(root, node->parent->value);

					node->parent->Red = 0;
					node->parent->parent->Red = 1;
					node->parent->parent->left->Red = 0;

					ClearNode(node);
				}
				//���� � "�����" ���� ��� ������� ��������
				else {
					node->parent->left->Red = 1;
					node->parent->Red = 0;

					ClearNode(node);
				}
			}
			//���� ���� - ����� �������
			else {
				//���� � "�����" ���� ���� ���� �� ���� ������� ������� ����� ��� ������
				if (node->parent->right->left != nullptr && node->parent->right->left->Red) {
					RightRotate(root, node->parent->right->value);
					LeftRotate(root, node->parent->value);

					node->parent->Red = 0;

					ClearNode(node);
				}
				//���� � "�����" ���� ������ ���� ������� ������� ������
				else if (node->parent->right->right != nullptr && node->parent->right->right->Red) {
					LeftRotate(root, node->parent->value);

					node->parent->Red = 0;
					node->parent->parent->Red = 1;
					node->parent->parent->right->Red = 0;

					ClearNode(node);
				}
				//���� � ����� ���� ��� ������� ��������
				else {
					node->parent->right->Red = 1;
					node->parent->Red = 0;

					ClearNode(node);
				}
			}
		}
		//���� �������� ���� - ר����
		else {
			//���� ���� - ������ �������
			if (node == node->parent->right) {
				//���� "����" ���� - �������
				if (node->parent->left->Red) {
					//���� � ������� ���������� ������� ���� ���� �� ���� ������� �������*/
					if ((node->parent->left->right->left != nullptr && node->parent->left->right->left->Red) ||
						(node->parent->left->right->right != nullptr && node->parent->left->right->right->Red)) {
						LeftRotate(root, node->parent->left->value);
						RightRotate(root, node->parent->value);

						if (node->parent->parent->left->right != nullptr && node->parent->parent->left->right->Red)
							node->parent->parent->left->right->Red = 0;
						else
							node->parent->parent->left->Red = 0;

						ClearNode(node);
					}
					/*���� � ���������� ������� ��� ������� ��������*/
					else {
						RightRotate(root, node->parent->value);
						node->parent->parent->Red = 0;
						node->parent->left->Red = 1;

						ClearNode(node);
					}
				}
				/*���� ���� ������� - ר����*/
				else {
					/*���� � ����� ���� ������ ������� �������*/
					if (node->parent->left->right != nullptr && node->parent->left->right->Red) {
						LeftRotate(root, node->parent->left->value);
						RightRotate(root, node->parent->value);

						node->parent->parent->Red = 0;

						ClearNode(node);
					}
					/*���� � ����� ���� ����� ������� �������*/
					else if (node->parent->left->left != nullptr && node->parent->left->left->Red) {
						RightRotate(root, node->parent->value);

						node->parent->parent->left->Red = 0;

						ClearNode(node);
					}
					/*���� � ����� ��� ������� ���������*/
					else {
						node->parent->left->Red = 1;
						ClearNode(node);
					}
				}
			}
			/*���� ���� - ����� �������*/
			else {
				/*���� ���� ������� - �������*/
				if (node->parent->right->Red) {
					/*���� � ������ ���������� ������� ���� ���� �� ���� ������� �������*/
					if ((node->parent->right->left->right != nullptr && node->parent->right->left->right->Red) ||
						(node->parent->right->left->left != nullptr && node->parent->right->left->left->Red)) {
						RightRotate(root, node->parent->right->value);
						LeftRotate(root, node->parent->value);

						if (node->parent->parent->right->left != nullptr && node->parent->parent->right->left->Red)
							node->parent->parent->right->left->Red = 0;
						else
							node->parent->parent->right->Red = 0;

						ClearNode(node);
					}
					/*���� � ���������� ������� ��� ������� ��������*/
					else {
						LeftRotate(root, node->parent->value);
						node->parent->parent->Red = 0;
						node->parent->right->Red = 1;

						ClearNode(node);
					}
				}
				/*���� ���� ������� - ר����*/
				else {
					/*���� � ����� ���� ����� ������� �������*/
					if (node->parent->right->left != nullptr && node->parent->right->left->Red) {
						RightRotate(root, node->parent->right->value);
						LeftRotate(root, node->parent->value);

						node->parent->parent->Red = 0;

						ClearNode(node);
					}
					/*���� � ����� ���� ������ ������� �������*/
					else if (node->parent->right->right != nullptr && node->parent->right->right->Red) {
						RightRotate(root, node->parent->value);

						node->parent->parent->right->Red = 0;

						ClearNode(node);
					}
					/*���� � ����� ��� ������� ��������*/
					else {
						node->parent->right->Red = 1;
						ClearNode(node);
					}
				}
			}
		}
	}
}

void ClearNode(Node* node) {
	if (node->parent != nullptr)
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;

	delete node;
}

void Print(Node* root) {

	if (root == nullptr) return;

	Print(root->left);

	cout << "value: " << root->value << ", Color: " << (root->Red ? "RED" : "BLACK")
		<< ", Parent: " << (root->parent ? root->parent->value : 0) << endl;

	Print(root->right);
}

void LeftRotate(Node*& root, int value) { //����� �������

	Node* node = root;

	while (true) {
		if (node == nullptr) {
			cout << "��� ���� � ����� ������!";
			return;
		}
		else if (value < node->value)
			node = node->left;
		else if (value > node->value)
			node = node->right;
		else
			break;
	}

	Node* nodetmp = node->right; //������������� y

	node->right = nodetmp->left; //����� ��������� y ���������� ������ ���������� x

	if (nodetmp->left != nullptr)
		nodetmp->left->parent = node;

	nodetmp->parent = node->parent; //����� �������� Y

	if (node->parent == nullptr)    //����� ������� � �������� ����
		root = nodetmp;
	else if (node == node->parent->left)
		node->parent->left = nodetmp;
	else
		node->parent->right = nodetmp;

	nodetmp->left = node; //����� ������ ������� Y

	node->parent = nodetmp;
}

void RightRotate(Node*& root, int value) {

	Node* node = root;

	while (true) {

		if (node == nullptr) {
			cout << "��� ���� � ����� ���������!";
			return;
		}
		else if (value < node->value)
			node = node->left;
		else if (value > node->value)
			node = node->right;
		else
			break;
	}

	Node* nodetmp = node->left; //������������� Y

	node->left = nodetmp->right; //������ ��������� Y ���������� ����� ���������� x

	if (nodetmp->right != nullptr)
		nodetmp->right->parent = node;

	nodetmp->parent = node->parent; //����� �������� Y

	if (node->parent == nullptr)    //����� ������� � �������� ����
		root = nodetmp;
	else if (node == node->parent->left)
		node->parent->left = nodetmp;
	else
		node->parent->right = nodetmp;

	nodetmp->right = node; //����� ������ ������� Y

	node->parent = nodetmp;
}

//������� ������ ������� � �������� ������, � �������� ���������
Node* Find(Node* root, int value) {

	while (true) {
		if (root == nullptr) {
			cout << "��� ���� � ����� ���������!\n";
			return nullptr;
		}
		else if (value < root->value)
			root = root->left;
		else if (value > root->value)
			root = root->right;
		else
			return root;
	}
}
//����� ���� � ������������ ��������� � ������
int FindMax(Node* root) {
	while (root->right != nullptr)
		root = root->right;

	return root->value;
}

//����� ���� � ����������� ��������� � ������
int FindMin(Node* root) {
	while (root->left != nullptr)
		root = root->left;

	return root->value;
}

//������� ������� ��������� ������� � ���������� ��� ��������
int FindNearestMax(Node* root, int value) {

	while (true) {
		if (root == nullptr) {
			cout << "��� ���� � ����� ���������!" << endl;
			return 0;
		}
		else if (value < root->value)
			root = root->left;
		else if (value > root->value)
			root = root->right;
		else
			break;
	}

	if (root->right != nullptr) {
		root = root->right;
		while (root->left != nullptr)
			root = root->left;
		return root->value;
	}
	else {
		cout << "���� �������� ������������" << endl;
		return value;
	}
}

//������� ������� ��������� ������� � ���������� ��� ��������
int FindNearestMin(Node* root, int value) {

	while (true) {
		if (root == nullptr) {
			cout << "��� ���� � ����� ���������!";
			return 0;
		}
		else if (value < root->value)
			root = root->left;
		else if (value > root->value)
			root = root->right;
		else
			break;
	}

	if (root->left != nullptr) {
		root = root->left;
		while (root->right != nullptr)
			root = root->right;
		return root->value;
	}
	else {
		cout << "���� �������� �����������";
		return value;
	}
}