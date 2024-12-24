# BDU-TRK-Verilenlerin-Strukturlari-Module-For-Cpp
C++ proqramlaşdırma dilində , Priority Queue, Unordered Set, Unordered Map, Class, Module

# Task Manager System

Bu layihə **C++** dilində hazırlanmış bir tapşırıq idarəetmə sistemidir. Layihə tapşırıqların prioritetə əsasən idarə edilməsini təmin edir və verilənlər daimi yaddaşda saxlanılır.

---

## Tələblər

Layihəni işə salmaq üçün aşağıdakı tələbləri təmin etməlisiniz:

1. **C++ Compiler**: C++20 dəstəkləyən kompilyator (GCC 10.2 və ya daha yeni, Clang 11 və ya daha yeni).
2. **CMake**: Layihəni qurmaq üçün (opsional).
3. **IDE/Code Editor**: Visual Studio Code, CLion və ya hər hansı digər uyğun redaktor.

---

## Quraşdırma və İstifadə

1. **Layihəni klonlayın:**
   ```bash
   git clone <REPO_LINK>
   cd task-manager-system
   ```

2. **Kodu kompilyasiya edin:**
   ```bash
   g++ -std=c++20 -o TaskManager main.cpp -fmodules-ts
   ```

3. **Proqramı işə salın:**
   ```bash
   ./TaskManager
   ```

4. **Menyu vasitəsilə tapşırıqlar əlavə edin, silin, axtarın və ya icra edin.**

---

## Funksionallıq

**Task Manager System** aşağıdakı əsas funksionallıqlara malikdir:

1. **Tapşırıq əlavə etmək:** Yeni tapşırıq təsviri, prioriteti və əlavə məlumatları ilə əlavə olunur.
2. **Tapşırıqları göstərmək:** Bütün mövcud tapşırıqlar prioritet sırasına görə göstərilir.
3. **Tapşırığı icra etmək:** Ən yüksək prioritetli tapşırıq icra edilir və növbədən çıxarılır.
4. **Tapşırığı silmək:** Tapşırıq ID-sinə əsasən silinir.
5. **Tapşırığı axtarmaq:** Açarsözə əsasən təsvir və ya məlumatlarda axtarış aparılır.
6. **Prioriteti yeniləmək:** Mövcud tapşırığın prioritetini dəyişir.
7. **Daimi yaddaş:** Tapşırıqlar faylda saxlanılır və proqram işə düşəndə bərpa edilir.

---

## Metodların Detallı İzahı

### 1. `addTask`
- Yeni tapşırıq əlavə edir.
- **Parametrlər:**
  - `description`: Tapşırığın təsviri (string).
  - `priority`: Prioritet (int; 1-High, 2-Medium, 3-Low).
  - `details`: Ətraflı məlumat (string).
- **Nəticə:** Yeni tapşırıq əlavə olunur və növbəyə daxil edilir.

### 2. `showTasks`
- Mövcud tapşırıqları prioritet sırasına görə göstərir.
- **Nəticə:** Hər bir tapşırıq ID, təsvir, prioritet və əlavə məlumatları ilə birlikdə çap edilir.

### 3. `executeTask`
- Ən yüksək prioritetli tapşırığı növbədən çıxarır və icra edir.
- **Nəticə:** Tapşırıq növbədən çıxarılır və ID sistemdən silinir.

### 4. `deleteTask`
- ID əsasında tapşırığı sistemdən silir.
- **Parametrlər:**
  - `id`: Silinməli tapşırığın unikal ID-si (int).
- **Nəticə:** Tapşırıq sistemdən və yaddaşdan silinir.

### 5. `searchTasks`
- Verilən açarsözə əsasən tapşırıqları axtarır.
- **Parametrlər:**
  - `keyword`: Axtarış açarsözü (string).
- **Nəticə:** Uyğun tapşırıqlar çap edilir.

### 6. `updateTaskPriority`
- Mövcud tapşırığın prioritetini yeniləyir.
- **Parametrlər:**
  - `id`: Tapşırığın ID-si (int).
  - `newPriority`: Yeni prioritet (int; 1-High, 2-Medium, 3-Low).
- **Nəticə:** Tapşırığın prioriteti dəyişdirilir.

### 7. `saveTasksToFile`
- Bütün tapşırıqları faylda saxlayır.
- **Nəticə:** `tasks.txt` faylına tapşırıqlar yazılır.

### 8. `loadTasksFromFile`
- Faylda saxlanılan tapşırıqları yükləyir.
- **Nəticə:** `tasks.txt` faylından tapşırıqlar oxunur və növbəyə əlavə edilir.

---

## Proqramın İstifadəsi

Proqram işə düşəndə aşağıdakı menyu təqdim edilir:

```
---- Tapşırıq İdarəetmə Sistemi ----
1. Tapşırıq əlavə et
2. Tapşırıqları göstər
3. Tapşırığı icra et
4. Tapşırığı sil
5. Tapşırığı axtar
6. Tapşırığın prioritetini yenilə
7. Çıxış
Seçim: 
```

- Menyudan uyğun rəqəmi daxil edərək funksiyanı seçə bilərsiniz.
- Məsələn, tapşırıq əlavə etmək üçün **1** seçin və sizdən təsvir, prioritet və əlavə məlumat daxil etməyiniz istənəcək.

---

## Layihə Quruluşu

```
task-manager-system/
├── main.cpp          # Proqramın əsas faylı
├── task_manager.ixx  # Modulun interfeysi və implementasiyası
├── tasks.txt         # Daimi yaddaş üçün fayl (avtomatik yaradılır)
├── README.md         # Layihə sənədləşməsi
```

---

## Gələcək Təkmilləşdirmələr

- Tapşırıqları tarix və vaxta əsasən avtomatik icra etmək.
- Tapşırıqların qruplaşdırılması (məsələn, layihələrə görə).
- Fayl formatını JSON və ya XML olaraq dəyişmək.

---

Bu README.md faylı layihənizi GitLab-da paylaşmaq üçün tam uyğun şəkildə hazırlanıb. Əgər əlavə sualınız və ya dəyişiklik ehtiyacınız varsa, mənə bildirə bilərsiniz!