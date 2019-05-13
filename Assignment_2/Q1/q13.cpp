#include <iostream>
#include <vector>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
struct square
{
    std::string up;
    std::string left;
    std::string down;
    std::string right;
    
    int id;
};

bool operator<(const square &lhs, const square &rhs) { return lhs.id < rhs.id; }

struct square_puzzle
{
    void insert(square sq)
    {
        if(sq.up == black && sq.left == black)
            left_up = std::move(sq);
        else if(sq.left == black && sq.down == black)
            left_down = std::move(sq);
        else if(sq.down == black && sq.right == black)
            right_down = std::move(sq);
        else if(sq.right == black && sq.up == black)
            right_up = std::move(sq);
        else if(sq.up == black)
            up.emplace_back(std::move(sq));
        else if(sq.left == black)
            left.emplace_back(std::move(sq));
        else if(sq.down == black)
            down.emplace_back(std::move(sq));
        else if(sq.right == black)
            right.emplace_back(std::move(sq));
        else middle.emplace_back(std::move(sq));
    }

    bool check_borders()
    {
        for(int i = 0; i < up.size(); ++i)
            if(up[i].down != middle[i].up) return false;

        for(int i = 0; i < left.size(); ++i)
            if(left[i].right != middle[i * left.size()].left) return false;

        for(int i = 1; i <= down.size(); ++i)
            if(down[down.size()-i].up != middle[middle.size()-i].down) return false;

        for(int i = 0; i < right.size(); ++i)
            if(right[i].left != middle[i * right.size() + (right.size()-1)].right) return false;

        return true;
    }

    void permutate_until_correct_square()
    {
        cout<<1<<endl;
        while(left_up.right != up[0].left or up[0].right != up[1].left or up.back().right != right_up.left) 
            std::next_permutation(up.begin(), up.end());
        cout<<2<<endl;
        while(left_down.right != down[0].left or down[0].right != down[1].left or down.back().right != right_down.left)
            std::next_permutation(down.begin(), down.end());
        cout<<3<<endl;
        while(left_up.down != left[0].up or left[0].down != left[1].up or left.back().down != left_down.up)
            std::next_permutation(left.begin(), left.end());
        cout<<4<<endl;
        while(right_up.down != right[0].up or right[0].down != right[1].up or right.back().down != right_down.up)
            std::next_permutation(right.begin(), right.end());
        cout<<5<<endl;
        while(not check_borders())
             std::next_permutation(middle.begin(), middle.end());
    }

    void print_first_row(FILE *fp)
    {
        int i;
        string ss="";
        std::cout << '(' << left_up.up << ',' << left_up.left << ',' << left_up.down << ',' << left_up.right << ");";
        ss='('+left_up.up+','+left_up.left+','+left_up.down+','+left_up.right+");";
        for(auto & square : up)
        {
            std::cout << '(' << square.up << ',' << square.left << ',' << square.down << ',' << square.right << ");";
            ss+='('+square.up+','+square.left+','+square.down+','+square.right+");";
        }
        std::cout << '(' << right_up.up << ',' << right_up.left << ',' << right_up.down << ',' << right_up.right << ")" << std::endl;
        ss+='('+right_up.up+','+right_up.left+','+right_up.down+','+right_up.right+")\n";
        if (fp)
        {
            for(int i=0; i<ss.size(); i++) 
                putc(ss[i],fp);
        }
            
    }

    void print_middle_rows(FILE *fp)
    {
        int zz;
        string ss="";
        for(int i = 0, j = 0; i < left.size(); ++i) 
        {
            ss="";
            std::cout << '(' << left[i].up << ',' << left[i].left << ',' << left[i].down << ',' << left[i].right << ");";
            ss='('+left[i].up+','+left[i].left+','+left[i].down+','+left[i].right+");";
            for(int k = 0; k < up.size(); ++k, ++j)
            {
                std::cout << '(' << middle[j].up << ',' << middle[j].left << ',' << middle[j].down << ',' << middle[j].right << ");";
                ss+='('+middle[j].up+','+middle[j].left+','+middle[j].down+','+middle[j].right+");";
            }
            std::cout << "(" << right[i].up << ',' << right[i].left << ',' << right[i].down << ',' << right[i].right << ")" << std::endl;
            ss+='('+right[i].up+','+right[i].left+','+right[i].down+','+right[i].right+")\n";
            if (fp)
            {
                for(int zz=0; zz<ss.size(); zz++) 
                    putc(ss[zz],fp);
            }

        }
    }

    void print_last_row(FILE *fp)
    {
        int i;
        string ss="";
        ss='('+left_down.up+','+left_down.left+','+left_down.down+','+left_down.right+");";
        std::cout << '(' << left_down.up << ',' << left_down.left << ',' << left_down.down << ',' << left_down.right << ");";
        for(auto & square : down)
        {
            std::cout << '(' << square.up << ',' << square.left << ',' << square.down << ',' << square.right << ");";
            ss+='('+square.up+','+square.left+','+square.down+','+square.right+");";
        }
        ss+='('+right_down.up+','+right_down.left+','+right_down.down+','+right_down.right+")\n";
        std::cout << '(' << right_down.up << ',' << right_down.left << ',' << right_down.down << ',' << right_down.right << ")" << std::endl;
        if (fp)
        {
            for(int i=0; i<ss.size(); i++) 
                putc(ss[i],fp);
        }
    }

    void print()
    {
        FILE *fp;
        fp = fopen("output1.txt", "w");
        print_first_row(fp);
        print_middle_rows(fp);
        print_last_row(fp);
        fclose(fp);
    }

    square left_up, left_down, right_up, right_down;
    std::vector<square> up, left, down, right, middle;
    
    const std::string black = "black";
};


int main ()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int id = 0;
    square_puzzle puzzle;
    std::string up, left, down, right, tmp;
    int i;
    int c;
    ifstream fin; 
    string line,s,ss[4];
    // by default open mode = ios::in mode 
    fin.open("input1.txt"); 
    while (fin) { 
  
        // Read a Line from File 
        if(fin.eof())
        {
            break;
        }
        c=0;
        getline(fin, line); 
  
        // Print line in Console 
        cout << line << endl; 
        s="";
        for(i=0;i<line.size();i++)
        {
            if(!(line[i]=='(' || line[i]==')' || line[i]==' '))
            {
                if(line[i]==',')
                {
                    ss[c]=s;
                    c++;
                    s="";
                }
                else
                {
                    s+=line[i];
                }
            }
        }
        ss[c]=s;
        up=ss[0];
        left=ss[1];
        down=ss[2];
        right=ss[3];
        puzzle.insert(square{std::move(up), std::move(left), std::move(down), std::move(right), id++});
    } 
    // while(t--)
    // {
    //     getline(std::cin, up, ',');
    // 	cout<<up<<" ";
    //     up = up.substr(1);
    //     cout<<up<<" ";
    //     getline(std::cin, left, ',');
    //     getline(std::cin, down, ',');
    //     getline(std::cin, right, ')');
    //     cout<<left<<" "<<down<<" "<<right<<"\n";
    //     right = right.substr(0, right.size());
    //     cout<<right<<endl;
    //     getline(std::cin, tmp, '\n');
    //     puzzle.insert(square{std::move(up), std::move(left), std::move(down), std::move(right), id++});
    // }
 
    puzzle.permutate_until_correct_square();
    puzzle.print();

    return 0;
}
