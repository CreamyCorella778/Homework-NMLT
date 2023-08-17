#include "Header1.hpp"
#include "Header2.hpp"

// Xem ho so ca nhan & doi mat khau
int task1(string email)
{
    int func = 0;
    do
    {
        cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
            << "1. Xem ho so ca nhan" << endl
            << "2. Doi mat khau" << endl
            << "Cac so khac. Dang xuat:";
        cin >> func;
        switch (func)
        {
        case 1:
            printProfileIn4(email);
            break;
        case 2:
        {
            string fname = "login.csv.txt";
            changePassword(fname, email);
            break;
        }
        }
    } while (func == 1 || func == 2);
    return 0;
}

// tao hoc ki moi khi chua co
void task2()
{
    Semester curr;
    int no = 0;  SchoolYear sy; Date sd, ed;
    getSemesterIn4(no, sy, sd, ed);
    curr = createSemester(no, sy, sd, ed);
    cout << "Hoc ki vua them la: " << endl;
    viewSemester(curr);
    Node<Semester>* node = new Node<Semester>; node->init(curr);
    addLast(systems.allSemester, node);
}

// tao mot khoa hoc moi
bool task3(Semester currSem)
{
    Course cour; 
    getCourseIn4(cour, currSem);
    if (!addCoursetoSemester(cour, currSem))
    {
        cout << "Loi he thong. Chuc ban may man lan sau" << endl;
        return false;
    }
    Node<Course>* nut = new Node<Course>; nut->init(cour);
    addLast(cour.teacher.courses, nut);
    cout << "Hoc ki vua them la: " << endl;
    viewCourse(cour);
    return true;
}

// nhap danh sach hoc sinh tu tep vao khoa hoc
bool task4(Semester currSem)
{
    string fname = "", cou = "", cls = ""; Node<Course>* course = new Node<Course>; int func = 0, times = 5;
    do
    {
        cout << "Nhap ten tep can tai len: "; getline(cin, fname);
        cout << "Nhap ma khoa hoc: "; getline(cin, cou);
        cout << "Nhap ten lop: "; getline(cin, cls);
        course = findCourse(cou, cls, currSem.number);
        --times;
        if (!course)
            cout << "Khong tim thay khoa hoc. Moi nhap lai. Ban co " << times << " lan nhap: " << endl;
    } while (!course );
    if (!addStudentsToCourse(fname, course->data))
    {
        cout << "Loi he thong. Chuc ban may man lan sau" << endl;
        return false;
    }
    else
    {
        cout << "Them thanh cong. Ban co muon xem danh sach hoc sinh da them khong?" << endl
        << "Chon so thu tu tuong ung voi lua chon:" << endl
        << "1. Co                        2. Khong: ";
        cin >> func;
        if (func == 1)
            viewStudents(course->data);
        return true;
    }
}

bool task5(Semester currSem)
{
    string cou = "", cls = ""; int option = 0, so_lan = 5; bool done = false;
    do
    {
        cout << "Nhap lan luot ma khoa hoc va ten lop hoc: "; getline(cin, cou); getline(cin, cls);
        getIn4toUpdateCourse(cou, cls, option);
        done = updateCourseIn4(cou, cls, option, getIn4toUpdateCourse(option), currSem);
        --so_lan;
        if (!done)
            cout << "Khong tim duoc khoa hoc, giao vien hoac lop. Moi nhap lai. Ban con: " << so_lan << "nhap." << endl;
    } while (!done && so_lan > 0);
    if (!done) // so_lan == 0
        return false;
    cout << "Cap nhat thanh cong. Ban co muon xem khoa hoc khong?" << endl
        << "Chon so thu tu tuong ung voi lua chon: " << endl
        << "1. Co                        2. Khong: ";
    cin >> option;
    if (option == 1)
    {
        viewCourse(findCourse(cou, cls, currSem.number)->data);
}
}