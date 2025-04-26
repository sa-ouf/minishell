int main()
{
    void *mlx;
    void *win;
    int i = 0;
    int j;
    void *img;
    char arr[6][7] = {
                 {,1 1, 1, 1, 1, 1, 1}
                ,{1, 0, 0, 2, 0, 0, 1}
                ,{1, 0, 2, 0, 2, 0, 1}
                ,{1, 2, 2, 2, 2, 2, 1}
                ,{1, 0, 0, 0, 0, 0, 1}
                ,{1, 1, 1, 1, 1, 1, 1}
            }

    mlx = mlx_init();
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, 800, 600, "window");
    if (!win)
        return (1);
    img = mlx_xpm_file_to_image(mlx, "cercel.xpm", 0, 0);
    if (!img)
        return (1);
    while (i < 6)
    {  
        j = 0;
        while (j < 7)
        {
            if (arr[i][j] == '2')
                mlx_put_image_to_window(mlx, win, img, 10, 10);
            j++;
        }
        i++;
    }
    mlx_loop(mlx);
}
