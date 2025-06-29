#include "datos.h"
#include "estructuras.h"
#include "funciones.h"
#include <cstring>

// Definir las variables globales
NodoProducto *catalogoPorCategoria[MAX_CATEGORIAS] = {nullptr};
NodoUsuario *arbolUsuarios = nullptr;

void inicializarDatos() {
  // Crear productos de ejemplo
  Producto *p1 = new Producto{1, "Smartphone X", "TechMax", 499.99f, 4, 0};
  Producto *p2 = new Producto{2, "Laptop Pro", "TechMax", 899.99f, 5, 0};
  Producto *p3 =
      new Producto{3, "Cafetera Premium", "HomeGoods", 129.99f, 4, 1};
  Producto *p4 =
      new Producto{4, "Zapatillas Running", "SportLife", 89.99f, 3, 3};
  Producto *p5 =
      new Producto{5, "Crema Hidratante", "BeautyCare", 24.99f, 4, 4};

  // Nuevos productos
  Producto *p6 = new Producto{6, "Tablet Ultra", "TechMax", 350.00f, 4, 0};
  Producto *p7 = new Producto{7, "Auriculares Inalambricos", "SoundWave", 150.50f, 5, 0};
  Producto *p8 = new Producto{8, "Smartwatch Fit", "TechMax", 199.99f, 4, 0};
  Producto *p9 = new Producto{9, "Teclado Mecanico Gamer", "KeyMaster", 120.00f, 5, 0};
  Producto *p10 = new Producto{10, "Monitor Curvo 27", "ViewSonic", 300.00f, 4, 0};
  Producto *p11 = new Producto{11, "Raton Ergonomico", "Logi", 75.99f, 4, 0};
  Producto *p12 = new Producto{12, "Camara de Seguridad WiFi", "SecureHome", 99.99f, 3, 0};
  Producto *p13 = new Producto{13, "Power Bank 20000mAh", "Anker", 45.50f, 5, 0};
  Producto *p14 = new Producto{14, "Altavoz Bluetooth Portatil", "JBL", 110.00f, 4, 0};
  Producto *p15 = new Producto{15, "Router WiFi 6", "NetGear", 180.75f, 5, 0};
  Producto *p16 = new Producto{16, "Aspiradora Robot", "CleanBot", 250.00f, 4, 1};
  Producto *p17 = new Producto{17, "Set de Cuchillos de Chef", "KitchenPro", 85.00f, 5, 1};
  Producto *p18 = new Producto{18, "Freidora de Aire", "HomeGoods", 99.99f, 4, 1};
  Producto *p19 = new Producto{19, "Juego de Sabanas Queen", "ComfortSleep", 60.25f, 4, 1};
  Producto *p20 = new Producto{20, "Lampara de Escritorio LED", "BrightIdea", 35.00f, 3, 1};
  Producto *p21 = new Producto{21, "Purificador de Aire", "PureAir", 150.00f, 4, 1};
  Producto *p22 = new Producto{22, "Batidora de Vaso", "BlendIt", 70.00f, 4, 1};
  Producto *p23 = new Producto{23, "Toallas de Bano (Juego de 4)", "SoftTouch", 40.99f, 5, 1};
  Producto *p24 = new Producto{24, "Olla de Coccion Lenta", "CrockPot", 55.50f, 4, 1};
  Producto *p25 = new Producto{25, "Organizador de Armario", "NeatFreak", 25.00f, 3, 1};
  Producto *p26 = new Producto{26, "Camisa de Lino", "UrbanStyle", 45.00f, 4, 2};
  Producto *p27 = new Producto{27, "Pantalones Vaqueros Slim", "DenimCo", 70.00f, 5, 2};
  Producto *p28 = new Producto{28, "Vestido de Verano", "FloralChic", 65.50f, 4, 2};
  Producto *p29 = new Producto{29, "Bolso de Cuero", "LuxHandbags", 180.00f, 5, 2};
  Producto *p30 = new Producto{30, "Gafas de Sol Aviador", "Sunnies", 120.00f, 4, 2};
  Producto *p31 = new Producto{31, "Reloj Analogico Clasico", "Timeless", 250.99f, 5, 2};
  Producto *p32 = new Producto{32, "Chaqueta Impermeable", "OutdoorGear", 110.00f, 4, 2};
  Producto *p33 = new Producto{33, "Botines de Piel", "WalkEasy", 95.00f, 4, 2};
  Producto *p34 = new Producto{34, "Cinturon de Piel", "StyleBelt", 38.75f, 4, 2};
  Producto *p35 = new Producto{35, "Bufanda de Lana", "WarmHugs", 29.99f, 5, 2};
  Producto *p36 = new Producto{36, "Balon de Futbol", "SportLife", 22.00f, 4, 3};
  Producto *p37 = new Producto{37, "Rueda Abdominal", "FitCore", 19.99f, 3, 3};
  Producto *p38 = new Producto{38, "Botella de Agua Termica", "HydroFlask", 35.00f, 5, 3};
  Producto *p39 = new Producto{39, "Cuerda para Saltar", "JumpFit", 15.50f, 4, 3};
  Producto *p40 = new Producto{40, "Esterilla de Yoga", "ZenMat", 30.00f, 4, 3};
  Producto *p41 = new Producto{41, "Pesas Rusas (16kg)", "IronBell", 45.00f, 5, 3};
  Producto *p42 = new Producto{42, "Bandas de Resistencia (Set)", "FlexiBand", 25.00f, 4, 3};
  Producto *p43 = new Producto{43, "Camiseta Tecnica Transpirable", "SportLife", 28.99f, 4, 3};
  Producto *p44 = new Producto{44, "Guantes de Gimnasio", "PowerGrip", 18.00f, 3, 3};
  Producto *p45 = new Producto{45, "Monitor de Actividad", "FitTrack", 60.00f, 4, 3};
  Producto *p46 = new Producto{46, "Serum Facial con Vitamina C", "BeautyCare", 32.50f, 5, 4};
  Producto *p47 = new Producto{47, "Protector Solar SPF 50", "SunBlock", 18.99f, 4, 4};
  Producto *p48 = new Producto{48, "Set de Brochas de Maquillaje", "ProBrush", 40.00f, 4, 4};
  Producto *p49 = new Producto{49, "Champu Reparador", "HairRevive", 15.00f, 4, 4};
  Producto *p50 = new Producto{50, "Mascarilla Facial de Arcilla", "PureSkin", 20.75f, 4, 4};
  Producto *p51 = new Producto{51, "Aceite para Barba", "BeardGroom", 22.00f, 4, 4};
  Producto *p52 = new Producto{52, "Esmalte de Unas Larga Duracion", "NailPolishCo", 9.99f, 3, 4};
  Producto *p53 = new Producto{53, "Limpiador Facial Suave", "GentleCleanse", 16.50f, 5, 4};
  Producto *p54 = new Producto{54, "Crema de Manos Reparadora", "HandCare", 12.00f, 4, 4};
  Producto *p55 = new Producto{55, "Perfume Floral", "ScentGarden", 75.00f, 5, 4};

  agregarProductoACategoria(p1);
  agregarProductoACategoria(p2);
  agregarProductoACategoria(p3);
  agregarProductoACategoria(p4);
  agregarProductoACategoria(p5);
  agregarProductoACategoria(p6);
  agregarProductoACategoria(p7);
  agregarProductoACategoria(p8);
  agregarProductoACategoria(p9);
  agregarProductoACategoria(p10);
  agregarProductoACategoria(p11);
  agregarProductoACategoria(p12);
  agregarProductoACategoria(p13);
  agregarProductoACategoria(p14);
  agregarProductoACategoria(p15);
  agregarProductoACategoria(p16);
  agregarProductoACategoria(p17);
  agregarProductoACategoria(p18);
  agregarProductoACategoria(p19);
  agregarProductoACategoria(p20);
  agregarProductoACategoria(p21);
  agregarProductoACategoria(p22);
  agregarProductoACategoria(p23);
  agregarProductoACategoria(p24);
  agregarProductoACategoria(p25);
  agregarProductoACategoria(p26);
  agregarProductoACategoria(p27);
  agregarProductoACategoria(p28);
  agregarProductoACategoria(p29);
  agregarProductoACategoria(p30);
  agregarProductoACategoria(p31);
  agregarProductoACategoria(p32);
  agregarProductoACategoria(p33);
  agregarProductoACategoria(p34);
  agregarProductoACategoria(p35);
  agregarProductoACategoria(p36);
  agregarProductoACategoria(p37);
  agregarProductoACategoria(p38);
  agregarProductoACategoria(p39);
  agregarProductoACategoria(p40);
  agregarProductoACategoria(p41);
  agregarProductoACategoria(p42);
  agregarProductoACategoria(p43);
  agregarProductoACategoria(p44);
  agregarProductoACategoria(p45);
  agregarProductoACategoria(p46);
  agregarProductoACategoria(p47);
  agregarProductoACategoria(p48);
  agregarProductoACategoria(p49);
  agregarProductoACategoria(p50);
  agregarProductoACategoria(p51);
  agregarProductoACategoria(p52);
  agregarProductoACategoria(p53);
  agregarProductoACategoria(p54);
  agregarProductoACategoria(p55);

  // Crear usuarios
  Usuario *u1 = new Usuario();
  strcpy(u1->nombre, "Ana");
  strcpy(u1->apellido, "García");
  u1->id = 1001;
  strcpy(u1->username, "ana_user");
  strcpy(u1->password, "pass123");
  u1->rol = CLIENTE;
  inicializarHistorial(u1->historial);
  agregarPreferencia(u1->preferenciasMarcas, "TechMax");
  agregarPreferencia(u1->preferenciasMarcas, "HomeGoods");
  agregarAlHistorial(u1->historial, p1);
  agregarAlHistorial(u1->historial, p3);
  agregarAlHistorial(u1->historial, p2);
  agregarAlHistorial(u1->historial, p8);
  agregarAlHistorial(u1->historial, p18);


  Usuario *u2 = new Usuario();
  strcpy(u2->nombre, "Carlos");
  strcpy(u2->apellido, "Martínez");
  u2->id = 1002;
  strcpy(u2->username, "carlos_m");
  strcpy(u2->password, "pass456");
  u2->rol = CLIENTE;
  inicializarHistorial(u2->historial);
  agregarPreferencia(u2->preferenciasMarcas, "SportLife");
  agregarAlHistorial(u2->historial, p4);
  agregarAlHistorial(u2->historial, p36);
  agregarAlHistorial(u2->historial, p43);
  agregarAlHistorial(u2->historial, p45);


  Usuario *u3 = new Usuario();
  strcpy(u3->nombre, "Daniel");
  strcpy(u3->apellido, "Nuñez");
  u3->id = 1003;
  strcpy(u3->username, "daniel");
  strcpy(u3->password, "daniel");
  u3->rol = CLIENTE;
  inicializarHistorial(u3->historial);
  agregarPreferencia(u3->preferenciasMarcas, "SportLife");
  agregarAlHistorial(u3->historial, p37);
  agregarAlHistorial(u3->historial, p40);
  agregarAlHistorial(u3->historial, p41);

  Usuario *u4 = new Usuario();
  strcpy(u4->nombre, "Laura");
  strcpy(u4->apellido, "Sanchez");
  u4->id = 1004;
  strcpy(u4->username, "laura_s");
  strcpy(u4->password, "password4");
  u4->rol = CLIENTE;
  inicializarHistorial(u4->historial);
  agregarPreferencia(u4->preferenciasMarcas, "BeautyCare");
  agregarPreferencia(u4->preferenciasMarcas, "FloralChic");
  agregarAlHistorial(u4->historial, p5);
  agregarAlHistorial(u4->historial, p46);
  agregarAlHistorial(u4->historial, p28);
  agregarAlHistorial(u4->historial, p55);

  Usuario *u5 = new Usuario();
  strcpy(u5->nombre, "Pedro");
  strcpy(u5->apellido, "Gomez");
  u5->id = 1005;
  strcpy(u5->username, "pedro_g");
  strcpy(u5->password, "password5");
  u5->rol = CLIENTE;
  inicializarHistorial(u5->historial);
  agregarPreferencia(u5->preferenciasMarcas, "KitchenPro");
  agregarPreferencia(u5->preferenciasMarcas, "ViewSonic");
  agregarPreferencia(u5->preferenciasMarcas, "Logi");
  agregarAlHistorial(u5->historial, p17);
  agregarAlHistorial(u5->historial, p10);
  agregarAlHistorial(u5->historial, p11);


  //Crear usuario admin
  Usuario *admin = new Usuario();
  strcpy(admin->nombre, "Admin");
  strcpy(admin->apellido, "User");
  admin->id = 0;
  strcpy(admin->username, "admin");
  strcpy(admin->password, "admin");
  admin->rol = ADMIN;
  inicializarHistorial(admin->historial);


  // Insertar usuarios en el árbol
  insertarUsuario(arbolUsuarios, admin);
  insertarUsuario(arbolUsuarios, u1);
  insertarUsuario(arbolUsuarios, u2);
  insertarUsuario(arbolUsuarios, u3);
  insertarUsuario(arbolUsuarios, u4);
  insertarUsuario(arbolUsuarios, u5);
}
