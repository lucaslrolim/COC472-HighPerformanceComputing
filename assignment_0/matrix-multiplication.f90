program matrixMultiply
    implicit none
    ! Define seed and variables
    integer,parameter :: seed = 161095
    INTEGER :: i
    INTEGER :: j
    integer, parameter :: N = 51200 ! we need define n as a constant
    double precision start, finish

    double precision :: matrix(N,N)
    double precision :: vector(N)
    double precision :: resultCOL(N)
    double precision :: resultROW(N)

    double precision temp

    call srand(seed)

    ! Populate matrix
    do i = 1, N
        do j = 1, N
            matrix(i,j) = rand() * 100
        end do
    end do

    ! Populate vector
    do i = 1, N
        vector(i) = rand() * 100
    end do


    call cpu_time(start)

    ! Multiply matrix by vector (column based)
    do i = 1, N
        resultCOL(:) = resultCOL(:) + matrix(:,i) * vector(i)
    end do

    call cpu_time(finish)

    print '("Time (col based) = ",f6.3," seconds.")',finish-start

    call cpu_time(start)
    ! Multiply matrix by vector (row based)
    do i = 1, N
        resultROW(:) = SUM(matrix(i,:) * vector(:))
    end do

    call cpu_time(finish)

    print '("Time (row based) = ",f6.3," seconds.")',finish-start



end program matrixMultiply