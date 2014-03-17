class Tile {
    public:
	Tile();
	Tile(int size);
	void drawTile(int x, int y);
	void setTileSize(int size);
    private:
	int tileSize;
};
