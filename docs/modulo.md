# Lý thuyết số

## Nghịch đảo modulo (modulo inverse)

Nghích đảo modulo của một số nguyên $a$ là số nguyên $x$ sao cho $ax$ đồng dư với 1 theo modulo. Kí hiệu là
$$ax \equiv 1 \pmod{m} $$
Cũng có thể kí hiệu $x$ là $a^{-1}$.

Nghịch đảo modulo $x$ của một số nguyên $a$ tồn tại khi và chỉ khi $a$ và $x$ là cặp số nguyên tố cùng nhau (tức $gcd(a,x) = 1$)

## Các cách tìm nghịch đảo modulo

### 1. Sử dụng thuật toán Euclid mở rộng

Xét phương trình sau (với 2 ẩn $x$ và $y$)
$$ a \cdot x + m \cdot y = 1 $$
Ta thấy rằng khi $gcd(a,m) = 1 $ thì $x$ sẽ là nghịch đảo modulo của $a$. Lấy modulo m cho 2 vế ta được
$$a \cdot x \equiv 1 \pmod{m}$$
Cách cài đặt thuật toán như sau

```cpp
int extended_euclid(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    //cout << a << ' ' << b << ' ' << x << ' ' << y << '\n';
    return d;
}
int main(){
    int x,y;
    int g = extended_euclid(a,m,x,y);
    if (g!= 1){
        cout << "No solution";
    }
    else{
        x = (x+m)%m;
        cout << x;
    }
    return 0;
}
```

Time complexity: $O(log(max(a,b)))$

### 2. Sử dụng định lý Fermat nhỏ.

Theo định lý Euler ta có, nếu $a$ và $m$ là cặp số nguyên tố cùng nhau thì.
$$a^{\phi(m)} \equiv 1 \pmod{m}$$
với $\phi(m)$ là [hàm phi Euler](https://cp-algorithms.com/algebra/phi-function.html).
Nếu $m$ là một số nguyên tố thì $\phi(m) = m-1$, định lý Euler trở thành định lý Fermat nhỏ.
$$a^{m-1} \equiv 1 \pmod{m}$$
Nhân cả 2 vế cho $a^{-1}$, ta được

- Với $m$ không phải số nguyên tố. $a^{\phi(m)-1} \equiv a^{-1} \pmod{m}$
- Với $m$ là số nguyên tố. $a^{m-2} \equiv a^{-1} \pmod{m}$.

**Lưu ý:** Mặc dù dùng Fermat nhỏ dễ hiểu hơn. Nhưng nếu modulo $m$ không phải số nguyên tố thì cần tính hàm phi Euler => Cần khai triển thừa số nguyên tố tốn $O(\sqrt{N})$.

### 3. Sử dụng phép chia Euclid. (Euclidean Division)

Cho số nguyên tố $m > a$, theo phép chia Euclid, ta có.
$$m = k\cdot a + r$$
với $k = \lfloor \frac{m}{a} \rfloor $ và $r = m mod a$. Khi đó
$$0 \equiv k \cdot a + r \pmod{m}$$
$$r \equiv -k \cdot a \pmod{m}$$
$$r \cdot a^{-1} \equiv k \pmod{m}$$
$$ a^{-1} \equiv k \cdot r^{-1} \pmod{m}$$

**Lưu ý:**

- $m$ phải là số nguyên tố.
- Nếu $m$ là số nguyên tố, mọi $a \in[1,m-1]$ đều khả nghịch với $m$. Từ đó, ta có được thuật toán tính nghịch đảo modulo như sau

```cpp
    int inv(int a){
        return a <= 1 ? a : m - (long long)(m/a)*inv(m%a)%m;
    }
```

Time complexity: Khoảng $O(\frac{logm}{loglogm})$. Xấp xỉ $O(logN)$.

Ngoài ra, ta cũng có thể tính trước nghịch đảo modulo cho các số trong đoạn $[1,m-1]$ trong $O(m)$

```cpp
    inv[1] = 1;
    for (int a = 2;a<m;++a){
        inv[i] = m - (long long)(m/a)*inv[m%a]%m;
    }
```
