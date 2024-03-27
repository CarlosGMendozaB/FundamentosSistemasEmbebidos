program control_GPIO
  implicit none
  character(len=50) :: command

  ! GPIO utilizados para generar numero
  integer :: GPIO_0 = 27
  integer :: GPIO_1 = 22
  integer :: GPIO_2 = 23
  integer :: GPIO_3 = 24
  integer :: GPIO_4 = 5
  integer :: GPIO_5 = 6
  integer :: GPIO_6 = 13
  integer :: GPIO_7 = 25

  ! En caso que no se pase algun valor
  if (command_argument_count() /= 1) then
    print*, "No hay comando"
    print*, "los comandos a utilizar es config, valor, cerrar"
    stop 2  ! Numero invalido de argumentos
  end if

  ! Configurar GPIO como entradas
  call get_command_argument(1, command)
  if (trim(command) == "config") then
    ! Configurar los GPIO
    call export_gpio(GPIO_0)
    call export_gpio(GPIO_1)
    call export_gpio(GPIO_2)
    call export_gpio(GPIO_3)
    call export_gpio(GPIO_4)
    call export_gpio(GPIO_5)
    call export_gpio(GPIO_6)
    call export_gpio(GPIO_7)
  end if

  ! Cierre de los puertos GPIO
  if (trim(command) == "cerrar") then
    ! Cerrar los GPIO
    call unexport_gpio(GPIO_0)
    call unexport_gpio(GPIO_1)
    call unexport_gpio(GPIO_2)
    call unexport_gpio(GPIO_3)
    call unexport_gpio(GPIO_4)
    call unexport_gpio(GPIO_5)
    call unexport_gpio(GPIO_6)
    call unexport_gpio(GPIO_7)
  end if

contains

  subroutine export_gpio(gpio_num)
    integer, intent(in) :: gpio_num
    character(len=100) :: export_cmd
    write(export_cmd, '(A,I2,A)') "/sys/class/gpio/export", gpio_num
    call system('echo "'//trim(export_cmd)//'" > /sys/class/gpio/export')
    call sleep(1)  ! para asegurar que se exporto correctamente
    call system('echo "in" > /sys/class/gpio/gpio'//trim(adjustl(itoa(gpio_num)))//'/direction')
  end subroutine export_gpio

  subroutine unexport_gpio(gpio_num)
    integer, intent(in) :: gpio_num
   character(len=100) :: unexport_cmd
    write(unexport_cmd, '(A,I2,A)') "/sys/class/gpio/unexport", gpio_num
    call system('echo "'//trim(unexport_cmd)//'" > /sys/class/gpio/unexport')
  end subroutine unexport_gpio


end program control_GPIO
