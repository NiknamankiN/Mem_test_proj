# Qt Project
Данный проект Qt Creator является частью программно-аппаратного обеспечения, предназначенного для функционального и параметрического тестирования микросхем памяти с последовательным интерфейсом.  
Для запуска проекта необходима установленная библиотека VISA от National Instruments (https://www.ni.com/ru-ru/support/downloads/drivers/download.ni-visa.html#442805). Она используется для подключения источника питания и мультиметра, а также их удалённого контроля.  
Комплекс состоит из ПК, микроконтроллера PIC18F4520, мультиметра DM3068, источника питания DP832A, а также объекта контроля - микросхемы памяти с последовательным интерфейсом I2C.
# Состав ПО
Программная часть для ПК состоит из нескольких классов:  
chip_param - предназначен для хранения прочитанных из файла параметров тестируемой микросхемы памяти;  
mainwindow - главное окно, в котором проверяется подключение по USB источника питания и мультиметра к ПК;  
paraminp - окно, предназначенное для ввода параметров питания микросхемы, передачи данных параметров в источник питания, и выбора COM порта подключения микроконтроллера, указания файла с заполненными параметрами микросхемы памяти, а также проверки подключения микроконтроллера и микросхемы памяти к микроконтроллеру;  
resultform - форма для вывода результатов тестирования, перед её появлением происходит обмен данными с микроконтроллером и непосредственно тестирование микросхемы памяти;  
testwindow - форма с выбором методов функционального тестирования и параметрического тестирования и указания файла, в который будут записаны результаты тестирования;  
Res.qrc - файл ресурсов с картинками, добавленными в интерфейс, картинка расположены в директории Pict.  
Для работы проекта необходима версия Qt не ниже 5.1, так как для обмена по UART с микроконтроллером используется библиотека QSerialPort.  
Программное обеспечение для микроконтроллера представлено в репозитории https://github.com/NiknamankiN/Mem_test_for_PIC18.  
# Изображения интерфейса:  
mainwindow:  
![image](https://user-images.githubusercontent.com/59146831/169151049-6bc64eea-2a77-401d-ac93-a1a8af3d75b7.png)  
paraminp:  
![image](https://user-images.githubusercontent.com/59146831/169151210-ee62fd2e-f778-4e4e-9185-6c01d7c7aef7.png)  
testwindow:  
![image](https://user-images.githubusercontent.com/59146831/169151326-63da62c6-9421-41b9-ae63-a97e41175576.png)  
resultform:  
![image](https://user-images.githubusercontent.com/59146831/169151566-4dca3b91-354b-4a73-b5c6-e6e07be74077.png)  

