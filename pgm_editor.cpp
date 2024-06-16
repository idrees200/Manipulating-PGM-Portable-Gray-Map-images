#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

void B_Sort(int a[], int s) {
    for (int i = 0; i < s - 1; i++) {
        for (int j = 0; j < s - 1 - i; j++) {
            if (a[j] < a[j + 1]) {
                int T = a[j];
                a[j] = a[j + 1];
                a[j + 1] = T;
            }
        }
    }
}

struct PGMImage {
    int H, W, MaxGray;
    string Comment;
    string MagicNo;
    vector<vector<int>> ImageData;

    PGMImage() {
        H = W = MaxGray = -1;
    }

    void Create(vector<vector<int>>& Img, int H, int W) {
        Img = vector<vector<int>>(H, vector<int>(W));
    }

    bool ReserveMemory() {
        if (H < 0 || W < 0)
            return false;
        Create(ImageData, H, W);
        return true;
    }

    bool LoadImage(char FileName[]) {
        ifstream FIN(FileName);
        if (!FIN.is_open())
            return false;

        getline(FIN, MagicNo);
        getline(FIN, Comment); // Reading the comment. Comment is optional

        if (Comment[0] != '#') { // If no comment, go back to the previous position and read dimensions
            FIN.clear();
            FIN.seekg(-Comment.size(), ios_base::cur);
        }

        FIN >> W >> H >> MaxGray;
        if (!ReserveMemory()) {
            FIN.close();
            return false;
        }

        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                FIN >> ImageData[r][c];
            }
        }

        FIN.close();
        return true;
    }

    bool SaveImage(char FileName[]) {
        if (H < 0)
            return false;

        ofstream FOUT(FileName);
        if (!FOUT.is_open())
            return false;

        FOUT << "P2" << endl
             << "# Created By MB For BDS-1A and BDS-1C" << endl
             << W << " " << H << endl
             << MaxGray << endl;

        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                FOUT << ImageData[r][c] << " ";
            }
            FOUT << endl;
        }
        FOUT.close();
        return true;
    }

    bool Create_Negative() {
        if (H < 0)
            return false;
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++)
                ImageData[r][c] = MaxGray - ImageData[r][c];
        }
        return true;
    }

    bool Mean_Filter(int FilterSize = 3) {
        if (H < 0)
            return false;
        vector<vector<int>> Temp;
        Create(Temp, H, W);
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                int k = 0;
                int SUM = 0;
                for (int i = r - FilterSize / 2; i <= r + FilterSize / 2; i++) {
                    for (int j = c - FilterSize / 2; j <= c + FilterSize / 2; j++) {
                        if (i >= 0 && i < H && j >= 0 && j < W) {
                            SUM += ImageData[i][j];
                            k++;
                        }
                    }
                }
                Temp[r][c] = SUM / k;
            }
        }
        ImageData = Temp;
        return true;
    }

    bool Median_Filter(int FilterSize = 3) {
        if (H < 0)
            return false;
        vector<vector<int>> Temp;
        Create(Temp, H, W);
        int D[100];
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                int k = 0;
                for (int i = r - FilterSize / 2; i <= r + FilterSize / 2; i++) {
                    for (int j = c - FilterSize / 2; j <= c + FilterSize / 2; j++) {
                        if (i >= 0 && i < H && j >= 0 && j < W) {
                            D[k] = ImageData[i][j];
                            k++;
                        }
                    }
                }
                B_Sort(D, k);
                Temp[r][c] = D[k / 2];
            }
        }
        ImageData = Temp;
        return true;
    }

    bool Rotate(double angle) {
        vector<vector<int>> Temp;
        Create(Temp, H, W);
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                int newr = r * cos(angle) + c * sin(angle);
                int newc = -r * sin(angle) + c * cos(angle);
                if (newr >= 0 && newr < H && newc >= 0 && newc < W)
                    Temp[newr][newc] = ImageData[r][c];
            }
        }
        ImageData = Temp;
        return true;
    }

    bool RotateClockwise() {
        if (H < 0)
            return false;
        vector<vector<int>> Temp;
        Create(Temp, W, H);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                Temp[j][H - 1 - i] = ImageData[i][j];
            }
        }
        swap(H, W);
        ImageData = Temp;
        return true;
    }

    bool RotateCounterClockwise() {
        if (H < 0)
            return false;
        vector<vector<int>> Temp;
        Create(Temp, W, H);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                Temp[W - 1 - j][i] = ImageData[i][j];
            }
        }
        swap(H, W);
        ImageData = Temp;
        return true;
    }

    bool SaveCounterClock(char FileName[]) {
        if (H < 0)
            return false;

        ofstream POUT(FileName);
        if (!POUT.is_open())
            return false;

        POUT << "P2" << endl
             << "# Created By MB For BDS-1A and BDS-1C" << endl
             << W << " " << H << endl
             << MaxGray << endl;

        for (int r = 0; r < H; r++) {
            for (int c = W - 1; c >= 0; c--) {
                POUT << ImageData[r][c] << " ";
            }
            POUT << endl;
        }
        POUT.close();
        return true;
    }

    bool FlipHorizontal() {
        if (H < 0)
            return false;
        for (int r = 0; r < H; r++) {
            reverse(ImageData[r].begin(), ImageData[r].end());
        }
        return true;
    }

    bool SaveFlipHorizontal(char FileName[]) {
        if (H < 0)
            return false;

        ofstream POUT(FileName);
        if (!POUT.is_open())
            return false;

        POUT << "P2" << endl
             << "# Created By MB For BDS-1A and BDS-1C" << endl
             << W << " " << H << endl
             << MaxGray << endl;

        for (int r = 0; r < H; r++) {
            for (int c = W - 1; c >= 0; c--) {
                POUT << ImageData[r][c] << " ";
            }
            POUT << endl;
        }
        POUT.close();
        return true;
    }

    bool FlipVertical() {
        if (H < 0)
            return false;
        reverse(ImageData.begin(), ImageData.end());
        return true;
    }

    bool SaveFlipVertical(char FileName[]) {
        if (H < 0)
            return false;

        ofstream POUT(FileName);
        if (!POUT.is_open())
            return false;

        POUT << "P2" << endl
             << "# Created By MB For BDS-1A and BDS-1C" << endl
             << W << " " << H << endl
             << MaxGray << endl;

        for (int r = H - 1; r >= 0; r--) {
            for (int c = 0; c < W; c++) {
                POUT << ImageData[r][c] << " ";
            }
            POUT << endl;
        }
        POUT.close();
        return true;
    }

    bool Resize(int NewH, int NewW) {
        if (H < 0)
            return false;
        vector<vector<int>> Temp;
        Create(Temp, NewH, NewW);
        double Rh = H / (double)NewH;
        double Rw = W / (double)NewW;
        for (int r = 0; r < NewH; r++) {
            for (int c = 0; c < NewW; c++) {
                Temp[r][c] = ImageData[(int)(r * Rh)][(int)(c * Rw)];
            }
        }
        H = NewH;
        W = NewW;
        ImageData = Temp;
        return true;
    }

    bool CropImage(int newH, int newW) {
        if (H < 0)
            return false;

        vector<vector<int>> Temp;
        Create(Temp, newH, newW);

        for (int r = 0; r < newH; r++) {
            for (int c = 0; c < newW; c++) {
                if (r < H && c < W) {
                    Temp[r][c] = ImageData[r][c];
                } else {
                    Temp[r][c] = 0; // Fill with black if new dimensions are larger
                }
            }
        }

        H = newH;
        W = newW;
        ImageData = Temp;

        return true;
    }
};

void ShowMenu() {
    cout << "1: Load PGM Image\n";
    cout << "2: Save PGM Image\n";
    cout << "3: Create Negative\n";
    cout << "4: Apply Mean Filter\n";
    cout << "5: Apply Median Filter\n";
    cout << "6: Rotate Clockwise\n";
    cout << "7: Rotate Counter Clockwise\n";
    cout << "8: Flip Horizontally\n";
    cout << "9: Flip Vertically\n";
    cout << "10: Resize Image\n";
    cout << "11: Crop Image\n";
    cout << "0: Exit\n";
}

int main() {
    PGMImage MyImage;
    char FileName[50];
    int Choice;
    int NewH, NewW;

    do {
        ShowMenu();
        cout << "Enter Your Choice: ";
        cin >> Choice;

        switch (Choice) {
            case 1:
                cout << "Enter File Name To Load: ";
                cin >> FileName;
                if (MyImage.LoadImage(FileName))
                    cout << "Image Loaded Successfully\n";
                else
                    cout << "Image Not Loaded\n";
                break;
            case 2:
                cout << "Enter File Name To Save: ";
                cin >> FileName;
                if (MyImage.SaveImage(FileName))
                    cout << "Image Saved Successfully\n";
                else
                    cout << "Image Not Saved\n";
                break;
            case 3:
                if (MyImage.Create_Negative())
                    cout << "Negative Created Successfully\n";
                else
                    cout << "Negative Not Created\n";
                break;
            case 4:
                if (MyImage.Mean_Filter())
                    cout << "Mean Filter Applied Successfully\n";
                else
                    cout << "Mean Filter Not Applied\n";
                break;
            case 5:
                if (MyImage.Median_Filter())
                    cout << "Median Filter Applied Successfully\n";
                else
                    cout << "Median Filter Not Applied\n";
                break;
            case 6:
                if (MyImage.RotateClockwise())
                    cout << "Image Rotated Clockwise Successfully\n";
                else
                    cout << "Image Not Rotated Clockwise\n";
                break;
            case 7:
                if (MyImage.RotateCounterClockwise())
                    cout << "Image Rotated Counter Clockwise Successfully\n";
                else
                    cout << "Image Not Rotated Counter Clockwise\n";
                break;
            case 8:
                if (MyImage.FlipHorizontal())
                    cout << "Image Flipped Horizontally Successfully\n";
                else
                    cout << "Image Not Flipped Horizontally\n";
                break;
            case 9:
                if (MyImage.FlipVertical())
                    cout << "Image Flipped Vertically Successfully\n";
                else
                    cout << "Image Not Flipped Vertically\n";
                break;
            case 10:
                cout << "Enter New Height: ";
                cin >> NewH;
                cout << "Enter New Width: ";
                cin >> NewW;
                if (MyImage.Resize(NewH, NewW))
                    cout << "Image Resized Successfully\n";
                else
                    cout << "Image Not Resized\n";
                break;
            case 11:
                cout << "Enter New Height: ";
                cin >> NewH;
                cout << "Enter New Width: ";
                cin >> NewW;
                if (MyImage.CropImage(NewH, NewW))
                    cout << "Image Cropped Successfully\n";
                else
                    cout << "Image Not Cropped\n";
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice. Please try again.\n";
        }
    } while (Choice != 0);

    return 0;
}
