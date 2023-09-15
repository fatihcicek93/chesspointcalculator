using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

class Colors
{
private:
    // Initiliazing the parameters
    float black_matrix[8][8];
    float white_matrix[8][8];
    float black_score = 0;
    float white_score = 0;

    // These vectores are to find whether the number three is knight or not
    vector<int> b_matrix_h = {}; // Black matrix of knight
    vector<int> w_matrix_h = {}; // White matrix of knight

public:

    // Accessing the private elements
    float Get_score(char color)
    {
        if (color=='s')
        {
            return black_score;
        }
        else (color = 'b');
        {
            return white_score;
        }
    }

    // Setting the elements of the black and white matrices to zero
    void Set_to_zero()
        {
            for (int i = 0; i < 8; ++i)
                {
                    for (int j = 0; j < 8; ++j)
                        {
                        black_matrix[i][j] = 0.0;
                        white_matrix[i][j] = 0.0;
                        }
                }
        }

    // placing chess pieces on a chessboard matrix
    void Place_pieces(unsigned int row, unsigned int column, string name)
    {
        if (name[1] == 's')
            {
                if (name[0] == 'a')
                {
                    // It's written to distinguish between the knight and bishop
                    vector<int> b_horse_loc = {static_cast<int>(row), static_cast<int>(Column_map(column))}; // Saving current black knight location data into a vector
                    b_matrix_h.insert(b_matrix_h.end(), b_horse_loc.begin(), b_horse_loc.end()); // Concatenate

                    black_matrix[row][Column_map(column)] = Piece_map(name[0]);
                }
                else
                {
                    black_matrix[row][Column_map(column)] = Piece_map(name[0]);
                }
            }
        else if(name[1] == 'b')
            {
                if (name[0] == 'a')
                {
                    // It's written to distinguish between the knight and bishop
                    vector<int> w_horse_loc = {static_cast<int>(row), static_cast<int>(Column_map(column))}; // Saving current white knight location data into a vector
                    w_matrix_h.insert(w_matrix_h.end(), w_horse_loc.begin(), w_horse_loc.end()); // Concatenate

                    white_matrix[row][Column_map(column)] = Piece_map(name[0]);
                }
                else
                {
                    white_matrix[row][Column_map(column)] = Piece_map(name[0]);
                }
            }
    }

    // Determining the column position data and identified the chess piece present in that column by using mapping.
    int Column_map(unsigned column) // Mapping column positions
    {
        map<int, int> mapping;
        mapping[1] = 0;
        mapping[4] = 1;
        mapping[7] = 2;
        mapping[10] = 3;
        mapping[13] = 4;
        mapping[16] = 5;
        mapping[19] = 6;
        mapping[22] = 7;
        return mapping[column];
    }

    int Piece_map(char name) // Mapping the chess pieces
    {
        map<char, int> mapping_piece;
        mapping_piece['p'] = 1.0;
        mapping_piece['a'] = 3.0;
        mapping_piece['f'] = 3.0;
        mapping_piece['k'] = 5.0;
        mapping_piece['v'] = 9.0;
        mapping_piece['s'] = 100.0;
        return mapping_piece[name];
    }

    //This section is written to access the elements of private matrices in main function
    float getMatrix(int row, int column,char anahtar)
    {
        // Depending on the value received by the key, which can be 's' or 'p',
        //the matrix was automatically determined and sent to the main function.
        float (*Chosen_matrix)[8][8];

        if (anahtar == 's')
            {
                Chosen_matrix = &black_matrix; // Selection of the black matrix
            }
        else if (anahtar == 'b')
            {
                Chosen_matrix = &white_matrix; // Selection of the white matrix
            }

        float eleman = (*Chosen_matrix)[row][column];

            if (eleman == 1.0f) // This is a pawn.
            {
                return eleman;
            }
            else if (eleman == 3.0f) // This is a bishop or a knight.
            {
                return eleman;
            }
            else if (eleman == 5.0f) // This is a castle.
            {
                return eleman;
            }

            else if (eleman == 9.0f) // This is a queen.
            {
                return eleman;
            }
            else if (eleman == 100.0f) // This is a king.
            {
                return eleman;
            }
            else
            {
                // Empty
                return eleman;
            }
    }

    // Calculating total points of each color
    void Calc_points()
        {
            for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j <8; j++)
                    {
                        if (black_matrix[i][j] < 101.0)
                        {
                            black_score += black_matrix[i][j];
                        }
                        if (white_matrix[i][j] < 101.0)
                        {
                            white_score += white_matrix[i][j];
                        }
                    }
                }
        cout<< "Black point: " <<black_score <<endl;
        cout <<"White point: " <<white_score<<endl;
        }

    // Threat situations were calculated.
    void point_calculator(int i,int j,char color)
    {

        if (getMatrix(i,j,color)==5.0f) // Analyzing  the castle's movements.
            {
                Castle_movements(i,j,color);
            }

        if (getMatrix(i,j,color)==3.0f) // Analyzing  the bishop's movements or knight's movements
            {
                char which_one = knight_or_bishop(i,j,color);
                if (which_one == 'a') // This is a knight
                {
                    Knight_movements(i,j,color); // Analyzing  the bishop's movements
                }
                else
                {
                    Bishop_movement(i,j,color); // Analyzing  the knight's movements
                }
            }

        if (getMatrix(i,j,color)==1.0f) // This is pawn
            {
                Pawn_movement(i,j,color); // Analyzing  the pawn.
            }

        if (getMatrix(i,j,color)==9.0f) // This is queen.
            {
                Bishop_movement(i,j,color); // Analyzing  the bishop's movements
                Castle_movements(i,j,color); // Analyzing  the knight's movements
            }
        if (getMatrix(i,j,color)==100.0f) // This is king.
            {
                // No need to do something.
                // I am aware that the king can also pose a threat.
                // However, I did not consider it in this case to avoid complicating the code.
            }
    }

    // Determination of whether knight or not
    char knight_or_bishop(int i,int j,char color)
    {
        vector<int> Loc_knight = {i,j};
        vector<int> selectedVector = {0, 0, 0, 0};

        if (color == 's')
                {
                    selectedVector = b_matrix_h;
                }
            else
                {
                    selectedVector = w_matrix_h;
                }

        // The length of the vector is a maximum of 4 because there can be a maximum of 2 knights and 2 bishops.
        if (b_matrix_h.size()>=2)
        {
            // Creating a temporary vector and copied the last two elements.
            vector<int> tempVector(selectedVector.end() - 2, selectedVector.end());

            // Deleting the last two elements of the vector.
            selectedVector.erase(selectedVector.end() - 2, selectedVector.end());

            if (Loc_knight == tempVector || Loc_knight == selectedVector)
            {
                return 'a';
            }
        }
        else
        {
            vector<int> Loc_knight = {i,j};

            if (Loc_knight == selectedVector)
            {
                return 'a';
            }
        }
    }

    void Pawn_movement(int i,int j,char color)
    {
    int counter = 1;
    char Oppo_color = getOppositeColor(color); //Opponent color

        if (color = 's') // moving piece's color is black
        {
            // If our moving piece is black, the directions of movement for the pawn are as follows.
            //
            ///////////////
            //           //
            //           //
            //     x     //
            // SW     SE //
            //           //
            ///////////////

            // Check in the SouthWest direction.
            if (getMatrix(i+counter,j-counter,Oppo_color)) // The white piece is under threat in SW direction.
                {
                    white_score = white_score - getMatrix(i+counter,j-counter,Oppo_color)/2; // The points of the threatened piece have been reduced by half.
                }
            // Check in the SouthEast direction.
            if (getMatrix(i+counter,j+counter,Oppo_color)) // The white piece is under threat in SE direction.
                {
                    white_score = white_score - getMatrix(i+counter,j+counter,Oppo_color)/2; // The points of the threatened piece have been reduced by half.
                }
        }

        else (color = 'b');
        {
            // If our moving piece is white, the directions of movement for the pawn are as follows.
            //
            ///////////////
            //           //
            // NW     NE //
            //     x     //
            //           //
            //           //
            ///////////////

            // Check in the NorthEast direction.
                if (getMatrix(i-counter,j+counter,Oppo_color)) // The black piece is under threat in NE direction.
                {
                    black_score = black_score - getMatrix(i-counter,j+counter,Oppo_color)/2; // The points of the threatened piece have been reduced by half.
                }
            // Check in the NorthWest direction.
                if (getMatrix(i-counter,j-counter,Oppo_color)) // The black piece is under threat in NW direction.
                {
                    black_score = black_score - getMatrix(i-counter,j-counter,Oppo_color)/2; // The points of the threatened piece have been reduced by half.
                }
        }
    }


    void Knight_movements(int i,int j,char color)
    {
        int counter = 1;
        char Oppo_color = getOppositeColor(color); // Obtaining opponent color

    //cout << "tasin satiri: " << i << " sutunu: "<<j<< endl;
    //cout << " "<<endl;
    while (counter <= 1)
        {
            // "If it doesn't go out of the chessboard, the knight can threaten 8 points.
            //
            ///////////////////
            //   NW_1 NE_1   //
            // NW_2     NE_2 //
            //       x       //
            // SW_2     SE_2 //
            //   SW_1 SE_1   //
            ///////////////////

            // "Movement in the SouthWest - 1 direction.
            if (i + counter +1 < 8 && j - counter >= 0)
                {
                    if (getMatrix(i+counter+1,j-counter,Oppo_color))
                    {
                        if (color == 's' ) // Black piece is moving
                            {
                                white_score = white_score - getMatrix(i+counter+1,j-counter,Oppo_color)/2; // The white piece is under threat in NW-1 direction.
                            }
                        if (color == 'b') // White piece is moving
                            {
                                black_score = black_score - getMatrix(i+counter+1,j-counter,Oppo_color)/2; // The black piece is under threat in NW-1 direction.
                            }

                    }
                }

            // Check in the SouthWest - 2 direction.
            if (i + counter < 8 && j - counter -1 >= 0)
                {
                    if (getMatrix(i+counter,j-counter-1,Oppo_color))
                    {
                        if (Oppo_color == 'b') // Black piece is moving
                        {
                            white_score = white_score - getMatrix(i+counter,j-counter-1,Oppo_color); // The white piece is under threat in NW-2 direction.
                        }
                        if (Oppo_color == 's') // White piece is moving
                            {
                            black_score = black_score - getMatrix(i+counter,j-counter-1,Oppo_color)/2; // The black piece is under threat in NW-2 direction.
                            }
                    }
                }

            // Check in the SouthEast - 1 direction.
            if (i + counter +1< 8 && j+counter < 8)
                {
                    if (getMatrix(i+counter+1,j+counter,Oppo_color))
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i+counter+1,j+counter,Oppo_color)/2; // The white piece is under threat in SE-1 direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i+counter+1,j+counter,Oppo_color)/2; // The black piece is under threat in SE-1 direction.
                                }
                        }
                    }

            // Check in the SouthEast - 2 direction.
            if (i + counter< 8 && j+counter+1 < 8)
                {
                    if (getMatrix(i+counter,j+counter+1,Oppo_color))
                    {
                        if (color == 's') // Black piece is moving
                            {
                                white_score = white_score - getMatrix(i+counter,j+counter+1,Oppo_color)/2; // The white piece is under threat in SE-2 direction.
                            }
                        if (color == 'b') // White piece is moving
                            {
                                black_score = black_score - getMatrix(i+counter,j+counter+1,Oppo_color)/2; // The black piece is under threat in SE-2 direction.
                            }
                    }
                }

            // Check in the NorthEast - 1 direction.
            if  (i-counter-1 >=0 && j+counter<8)
                {
                    if (getMatrix(i-counter-1,j+counter,Oppo_color))
                    {
                        if (color == 's') // Black piece is moving
                            {
                                white_score = white_score - getMatrix(i-counter-1,j+counter,Oppo_color)/2; // The white piece is under threat in NE-1 direction.
                            }
                        if (color == 'b') // White piece is moving
                            {
                                black_score = black_score - getMatrix(i-counter-1,j+counter,Oppo_color)/2; // The black piece is under threat in NE-1 direction.
                            }
                    }
                }

            // Check in the NorthEast - 2 direction.
            if  (i-counter >=0 && j+counter+1<8)
                {
                    if (getMatrix(i-counter,j+counter+1,Oppo_color))
                    {
                        if (color == 's') // Black piece is moving
                            {
                                white_score = white_score - getMatrix(i-counter,j+counter+1,Oppo_color)/2; // The white piece is under threat in NE-2 direction.
                            }
                        if (color == 'b') // White piece is moving
                            {
                                black_score = black_score - getMatrix(i-counter,j+counter+1,Oppo_color)/2; // The black piece is under threat in NE-2 direction.
                            }
                    }
                }

            // Check in the NorthWest - 1 direction.
            if (i - counter -1>= 0 && j-counter >=0)
                {
                    if (getMatrix(i-counter-1,j-counter,Oppo_color))
                        {
                            if (color == 's') // Black piece is moving
                                {
                                white_score = white_score - getMatrix(i-counter-1,j-counter,Oppo_color)/2; // The white piece is under threat in NW-1 direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                black_score = black_score - getMatrix(i-counter-1,j-counter,Oppo_color)/2; // The black piece is under threat in NW-1 direction.
                                }
                        }

                }
            // Check in the NorthWest - 2 direction.
            if (i - counter>= 0 && (j-counter-1)>=0)
                {
                    if (getMatrix(i-counter,j-counter-1,Oppo_color))
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i-counter,j-counter-1,Oppo_color)/2; // The white piece is under threat in NW-2 direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i-counter,j-counter-1,Oppo_color)/2; // The black piece is under threat in NW-2 direction.
                                }
                        }
                }
        counter++;
        }
    }

    void Bishop_movement(int i,int j,char color)
    {
        int counter = 1;
        char Oppo_color = getOppositeColor(color);

    //cout << "tasin satiri: " << i << " sutunu: "<<j<< endl;

    int SW_counter = 0;
    int SE_counter = 0;
    int NE_counter = 0;
    int NW_counter = 0;
    while (counter <= 8)
        {
            // The bishop's directions of movement are diagonal and as follows.
            //
            ///////////////
            //           //
            // NW     NE //
            //     x     //
            // SW     SE //
            //           //
            ///////////////

            // Check in the SouthWest direction.
            if (i + counter < 8 && j - counter >= 0)
                {
                    if (getMatrix(i+counter,j-counter,color)) // Threatened and threatening pieces of the same color.
                    {
                        SW_counter++; // So that we can easily skip and does not consideration any other situations.
                    }
                    else if (getMatrix(i+counter,j-counter,Oppo_color))
                    {
                        if (SW_counter == 0) // If SW_counter is equal to zero, it may encounter any opponents.
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i+counter,j-counter,Oppo_color)/2; // The white piece is under threat in SW direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i+counter,j-counter,Oppo_color)/2; // The black piece is under threat in SW direction.
                                }
                            SW_counter++; // So that we can easily skip and does not consideration any other situations.
                        }
                    }
                }

            // Check in the SouthEast direction.
            if (i + counter < 8 && j+counter < 8)
                {
                    if (getMatrix(i+counter,j+counter,color)) // Threatened and threatening pieces of the same color.
                    {
                        SE_counter++; // So that we can easily skip and does not consideration any other situations.
                    }
                    else if (getMatrix(i+counter,j+counter,Oppo_color))
                    {

                        if (SE_counter == 0) // If SE_counter is equal to zero, it may encounter any opponents.
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i+counter,j+counter,Oppo_color)/2; // The white piece is under threat in SE direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i+counter,j+counter,Oppo_color)/2; // The black piece is under threat in SE direction.
                                }
                            SE_counter++; // So that we can easily skip and does not consideration any other situations.
                        }
                    }
                }

            // Check in the NorthEast direction.
            if  (i - counter >=0 && j+counter<8)
                {
                    if (getMatrix(i-counter,j+counter,color)) // Threatened and threatening pieces of the same color.
                    {
                        NE_counter++; // So that we can easily skip and does not consideration any other situations.
                    }
                    else if (getMatrix(i-counter,j+counter,Oppo_color))
                    {
                        if (NE_counter == 0) // If NE_counter is equal to zero, it may encounter any opponents.
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i-counter,j+counter,Oppo_color)/2; // The white piece is under threat in NE direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i-counter,j+counter,Oppo_color)/2; // The black piece is under threat in NE direction.
                                }
                            NE_counter++;
                        }
                    }
                }

            // Movement in the NorthWest direction.
            if (i - counter >= 0 && j-counter >=0)
                {
                    if (getMatrix(i-counter,j-counter,color)) // Threatened and threatening pieces of the same color.
                    {
                        NW_counter++; // So that we can easily skip and does not consideration any other situations.
                    }
                    else if (getMatrix(i-counter,j-counter,Oppo_color))
                    {
                         if (NW_counter == 0) // If NW_counter is equal to zero, it may encounter any opponents.
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i-counter,j-counter,Oppo_color)/2; // The white piece is under threat in NW direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - (getMatrix(i-counter,j-counter,Oppo_color))/2; // The black piece is under threat in NW direction.
                                }
                            NW_counter++;
                        }
                    }
                }
        counter++;
        }
    }

   void Castle_movements(int i,int j,char color)
    {
    int counter = 1;
    char Oppo_color = getOppositeColor(color);

    int West_counter = 0;
    int East_counter = 0;
    int North_counter = 0;
    int South_counter = 0;
    while (counter <= 8)
        {
            // Check in the North direction.
            if (j - counter >= 0)
                {
                    if (getMatrix(i,j-counter,color)) // Threatened and threatening pieces of the same color.
                    {
                        West_counter++;
                    }
                    else if (getMatrix(i,j-counter,Oppo_color))
                    {
                         if (West_counter == 0) // If West_counter is equal to zero, it may encounter any opponents.
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i,j-counter,Oppo_color)/2; // The white piece is under threat in West direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i,j-counter,Oppo_color)/2; // The black piece is under threat in West direction.
                                }
                            West_counter++;
                        }
                    }
                }

            // Check in the East direction.
            if (j + counter < 8)
                {
                    if (getMatrix(i,j+counter,color)) // Threatened and threatening pieces of the same color.
                    {
                        East_counter++;
                    }
                    else if (getMatrix(i,j+counter,Oppo_color))
                    {
                        if (East_counter == 0) // If West_counter is equal to zero, it may encounter any opponents.
                        {
                             if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i,j+counter,Oppo_color)/2; // The white piece is under threat in East direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i,j+counter,Oppo_color)/2; // The black piece is under threat in East direction.
                                }
                            East_counter++;
                        }
                    }
                }

            // Check in the North direction.
            if  (i - counter >= 0)
                {
                    if (getMatrix(i-counter,j,color)) // Threatened and threatening pieces of the same color.
                    {
                        North_counter++;
                    }
                    else if (getMatrix(i-counter,j,Oppo_color))
                    {
                        if (North_counter == 0) // If North_counter is equal to zero, it may encounter any opponents.
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i-counter,j,Oppo_color)/2; // The white piece is under threat in North direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i-counter,j,Oppo_color)/2; // The black piece is under threat in North direction.
                                }
                            North_counter++;
                        }
                    }
                }

            // Check in the South direction.
            if (i + counter < 8)
                {
                    if (getMatrix(i+counter,j,color)) // Threatened and threatening pieces of the same color.
                    {
                        South_counter++;
                    }
                    else if (getMatrix(i+counter,j,Oppo_color))
                    {
                        if (South_counter == 0) // If South_counter is equal to zero, it may encounter any opponents.
                        {
                            if (color == 's') // Black piece is moving
                                {
                                    white_score = white_score - getMatrix(i+counter,j,Oppo_color)/2; // The white piece is under threat in South direction.
                                }
                            if (color == 'b') // White piece is moving
                                {
                                    black_score = black_score - getMatrix(i+counter,j,Oppo_color)/2; // The black piece is under threat in South direction.
                                }
                            South_counter++;
                        }
                    }
                }
        counter++;
        }
    }

    // Identifying opposite color
    char getOppositeColor(char color)
    {
        if (color == 's')
            {
            return 'b';
            }
        else if (color == 'b')
            {
            return 's';
            }
    }
};


int main()
{
    string feature;

    /// Open the text file.
    ifstream inputtxt("board2.txt");

    Colors object; // Creating an object.
    object.Set_to_zero(); // Setting the values to zero.

    if (inputtxt.is_open())
    {
        //I have attempted to process the data from a text document to create an array. First, I examined each line separately.
        for (int i = 0; i < 8; ++i)
        {
            if (getline(inputtxt, feature))
            {
                cout << "Row number:" << i + 1 << " Values: " << feature << endl;
                string chess_piece = "";

                // By creating the object, operations are performed one by one inside the class.
                for (int key = 0; feature.length() >= key; key++)
                {
                    if (feature[key] == 'p' || feature[key] == 'a' || feature[key] == 'f' || feature[key] == 'k' || feature[key] == 'v' || feature[key] == 's' || feature[key] == 'b' )
                        {
                            chess_piece += feature[key];
                            chess_piece += feature[key+1];
                            key++;
                            object.Place_pieces(i,key,chess_piece);
                        }
                    else
                    {
                        chess_piece.erase();
                    }
                }
            }
        }
    }

cout <<" "<<endl;
cout << "Calculations before the threat situation"<<endl;
object.Calc_points();

// A for loop that will encompass all the chessboard pixels.
for (int i = 0; i <8; ++i)
    {
        for (int j =0 ; j <8; ++j)
            {
                //Sending the abbreviation of the color I want to examine in particular.
                object.point_calculator(i,j,'s'); // Sending 's' because I want to examine the black pieces.
                object.point_calculator(i,j,'b'); // Sending 'b' because I want to examine the white pieces.
            }
    }

cout <<" "<<endl;
cout << "Calculations after the threat situation"<<endl;
cout << "Siyah puan: " << object.Get_score('s')<<endl;
cout << "Beyaz puan: " << object.Get_score('b')<<endl;

return 0;
}



