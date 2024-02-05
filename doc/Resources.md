# Chess Programming Resources
### Watch this first!
<https://www.youtube.com/watch?v=w4FFX_otR-4&t=145s&ab_channel=BartekSpitza>
### Main Resources
- <https://www.chessprogramming.org/Main_Page>
- <https://github.com/official-stockfish/Stockfish>
### Other Great Videos
- <https://www.youtube.com/watch?v=U4ogK0MIzqk&ab_channel=SebastianLague>
- <https://www.youtube.com/watch?v=n5vV4u-nKtw&t=51s&ab_channel=ChessProgramming>
- <https://www.youtube.com/watch?v=_vqlIPDR2TU&t=1927s&ab_channel=SebastianLague>
### This Entire Channel
- <https://www.youtube.com/@chessprogramming591>
## Topics
### Chess Rules
<https://www.chessprogramming.org/Chess>
### Bitboards
<https://www.chessprogramming.org/Bitboards>
<https://github.com/official-stockfish/Stockfish/blob/master/src/bitboard.h>
- BitChess uses Big-Endian Rank-File Mapping (not as common as Little-Ending Rank-File mapping, but BERF is easier to understand when using binary or hexidecimal numbers) <https://www.chessprogramming.org/Square_Mapping_Considerations>
- Bitchess has a Bitboard class that contains utility bitboards for certain things like masking operations. The class will eventually contain much of the move generation functions currently in Position.h
### Position (the board state)
<https://www.chessprogramming.org/Chess_Position>
<https://github.com/official-stockfish/Stockfish/blob/master/src/position.h>
- BitChess currently stores an individual bitboard for each piece type (regardless of color), each color (contains all piece types), and some redundant boards for simplicity (such as all pieces)
- BitChess will eventually store other useful information, such as castling rights
### Binary Bitwise Operations
<https://www.chessprogramming.org/General_Setwise_Operations>
- Very important to understand for all the bitboard related operations


