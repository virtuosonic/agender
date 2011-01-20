/ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   *   N a m e :             A g e n d e r T r a y . c p p 
   *   P u r p o s e :       C o d e   f o r   t h e   t r a y / n o t i f i c a t i o n / t a s k b a r / e t c   i c o n 
   *   A u t h o r :         G a b r i e l   E s p i n o z a 
   *   C o p y r i g h t :   G a b r i e l   E s p i n o z a 
   *   L i c e n s e :   G P L v 3 + 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * / 
 # i f d e f   _ _ B O R L A N D C _ _ 
 	 # p r a g m a   h d r s t o p 
 # e n d i f 
 
 # i n c l u d e   < w x / d e f s . h > 
 
 # i f   d e f i n e d   w x H A S _ T A S K _ B A R _ I C O N 
 
 # i n c l u d e   " A g e n d e r T r a y . h "  
 # i n c l u d e   " X m l N o t e s . h " 
 # i n c l u d e   < w x / c o l o r d l g . h > 
 # i n c l u d e   < w x / n u m d l g . h > 
 # i n c l u d e   < w x / m e n u . h > 
 # i n c l u d e   < w x / c o n f i g . h > 
 # i n c l u d e   < w x / a p p . h > 
 # i n c l u d e   < w x / c l i p b r d . h > 
 # i n c l u d e   < w x / d a t a o b j . h > 
 # i n c l u d e   < w x / m s g d l g . h >  
 # i n c l u d e   < w x / f i l e d l g . h > 
 # i n c l u d e   < w x / i n t l . h > 
 # i n c l u d e   < w x / r i c h t e x t / r i c h t e x t s y m b o l d l g . h > 
 
 
 B E G I N _ E V E N T _ T A B L E ( A g e n d e r T r a y , w x T a s k B a r I c o n ) 
 	 E V T _ T A S K B A R _ L E F T _ U P ( A g e n d e r T r a y : : O n L e f t ) 
 	 E V T _ M E N U ( I D _ S H O W , A g e n d e r T r a y : : O n M e n u S h o w ) 
 	 E V T _ M E N U ( I D _ H I D E , A g e n d e r T r a y : : O n M e n u H i d e ) 
 	 E V T _ M E N U _ R A N G E ( I D _ O P C 1 0 0 , I D _ O P C 2 5 , A g e n d e r T r a y : : O n M e n u O p c ) 
 	 E V T _ M E N U ( I D _ Y E A R S E L , A g e n d e r T r a y : : O n Y e a r S e l ) 
 	 E V T _ M E N U ( I D _ N O T E S _ C O L O U R , A g e n d e r T r a y : : O n M e n u N o t e s C o l o u r ) 
 	 E V T _ M E N U ( w x I D _ E X I T , A g e n d e r T r a y : : O n M e n u E x i t ) 
 	 E V T _ M E N U ( w x I D _ F I N D , A g e n d e r T r a y : : O n M e n u F i n d ) 
 	 E V T _ M E N U ( I D _ A U T O S T A R T , A g e n d e r T r a y : : O n M e n u A u t o S t a r t ) 
 	 E V T _ M E N U ( I D _ S Y M B O L , A g e n d e r T r a y : : O n M e n u S y m b o l s ) 
 	 E V T _ M E N U ( I D _ N O T I F Y , A g e n d e r T r a y : : O n M e n u N o t i f y )  
 	 E V T _ M E N U ( I D _ I M P O R T , A g e n d e r T r a y : : O n M e n u I m p o r t )  
 	 E V T _ M E N U ( I D _ E X P O R T , A g e n d e r T r a y : : O n M e n u E x p o r t ) 
 	 E V T _ M E N U _ R A N G E ( I D _ L A N G _ D E F , I D _ L A N G _ L A S T - 1 , A g e n d e r T r a y : : O n M e n u L a n g ) 
 E N D _ E V E N T _ T A B L E ( ) 
 
 A g e n d e r T r a y : : A g e n d e r T r a y ( w x F r a m e *   f r a m e ) 
 { 
 	 t h i s - > f r a m e   =   f r a m e ; 
 	 a l p h a   =   w x C o n f i g : : G e t ( ) - > R e a d ( _ T ( " / o p a c i t y " ) , 2 5 5 ) ; 
 	 s w i t c h   ( a l p h a ) 
 	 { 
 	 	 c a s e   2 5 5 : 
 	 	 	 o p c   =   I D _ O P C 1 0 0 ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   1 8 7 : 
 	 	 	 o p c   =   I D _ O P C 7 5 ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   1 2 5 : 
 	 	 	 o p c   =   I D _ O P C 5 0 ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   6 2 : 
 	 	 	 o p c   =   I D _ O P C 2 5 ; 
 	 	 	 b r e a k ; 
 
 	 	 d e f a u l t : 
 	 	 	 b r e a k ; 
 	 } 
 	 b o o l   a u t o s t a r t = t r u e ; 
 	 w x C o n f i g : : G e t ( ) - > R e a d ( _ T ( " / a u t o s t a r t " ) , & a u t o s t a r t , t r u e ) ; 
 	 a s t a r t . S e t ( a u t o s t a r t ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n L e f t ( w x T a s k B a r I c o n E v e n t &   W X U N U S E D ( e v e n t ) ) 
 { 
 	 / / s h o w   t h e   m a i n   w i n d o w 
 	 i f   ( f r a m e - > I s S h o w n O n S c r e e n ( ) ) 
 	 { 
 	 	 f r a m e - > H i d e ( ) ; 
 	 } 
 	 e l s e 
 	 { 
 	 	 f r a m e - > S h o w ( ) ; 
 	 	 f r a m e - > S e t F o c u s ( ) ; 
 	 	 f r a m e - > R a i s e ( ) ; 
 	 } 
 } 
 
 w x M e n u   *   A g e n d e r T r a y : : C r e a t e P o p u p M e n u ( ) 
 { 
 	 / / o p a c i t y   s u b m e n u 
 	 w x M e n u *   o p c M e n u ; 
 	 o p c M e n u   =   n e w   w x M e n u ; 
 	 o p c M e n u - > A p p e n d R a d i o I t e m ( I D _ O P C 1 0 0 , _ ( " 1 0 0 % " ) ) ; 
 	 o p c M e n u - > A p p e n d R a d i o I t e m ( I D _ O P C 7 5 , _ ( " 7 5 % " ) ) ; 
 	 o p c M e n u - > A p p e n d R a d i o I t e m ( I D _ O P C 5 0 , _ ( " 5 0 % " ) ) ; 
 	 o p c M e n u - > A p p e n d R a d i o I t e m ( I D _ O P C 2 5 , _ ( " 2 5 % " ) ) ; 
 	 o p c M e n u - > C h e c k ( o p c , t r u e ) ; 
 	 / / l a n g   s u b m e n u 
 	 w x M e n u *   l m e n u ; 
 	 l m e n u   =   n e w   w x M e n u ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ D E F , _ ( " d e f a u l t " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ E S , _ T ( " E s p a � o l " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ D E , _ T ( " D e u t c h " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ J A , _ T ( " �e,g��" ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ P T , _ T ( " P o r t u g u � s " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ F R , _ T ( " F r a n � a i s " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ E L , _ T ( " ��������" ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ S V , _ T ( " S v e n s k a " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ Z H _ H K , _ T ( " T r a d i t i o n a l   C h i n e s e " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ Z H _ C N , _ T ( " -N�e" ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ R O , _ T ( " R o m a n i a n " ) ) ; 
 	 l m e n u - > A p p e n d R a d i o I t e m ( I D _ L A N G _ H E , _ T ( " H e b r e w " ) ) ; 
 	 l o n g   l a n g   =   w x C o n f i g : : G e t ( ) - > R e a d ( _ T ( " / l a n g " ) , w x L A N G U A G E _ U N K N O W N ) ; 
 	 s w i t c h   ( l a n g ) 
 	 { 
 	 	 c a s e   w x L A N G U A G E _ S P A N I S H : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ E S , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ G E R M A N : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ D E , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ J A P A N E S E : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ J A , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ S W E D I S H : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ S V , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ F R E N C H : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ F R , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ P O R T U G U E S E : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ P T , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ G R E E K : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ E L , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ C H I N E S E _ T R A D I T I O N A L : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ Z H _ H K , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ C H I N E S E _ S I M P L I F I E D : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ Z H _ C N , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ H E B R E W : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ H E , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   w x L A N G U A G E _ R O M A N I A N : 
 	 	 	 l m e n u - > C h e c k ( I D _ L A N G _ R O , t r u e ) ; 
 	 	 	 b r e a k ; 
 	 	 d e f a u l t : 
 	 	 	 b r e a k ; 
 	 } 
 	 / / m a i n   m e n u 
 	 w x M e n u *   m e n u ; 
 	 m e n u   =   n e w   w x M e n u ; 
 	 m e n u - > A p p e n d ( I D _ S H O W , _ ( " S h o w " ) ) ; 
 	 m e n u - > A p p e n d ( I D _ H I D E , _ ( " H i d e " ) ) ; 
 	 m e n u - > A p p e n d S e p a r a t o r ( ) ; 
 	 i f   ( f r a m e - > C a n S e t T r a n s p a r e n t ( ) ) 
 	 	 m e n u - > A p p e n d S u b M e n u ( o p c M e n u , _ ( " O p a c i t y " ) ) ; 
 	 m e n u - > A p p e n d C h e c k I t e m ( I D _ Y E A R S E L , _ ( " Y e a r   s e l e c t o r " ) ) ; 
 	 m e n u - > A p p e n d ( I D _ N O T E S _ C O L O U R , _ ( " N o t e s   C o l o u r " ) ) ; 
 	 m e n u - > A p p e n d S u b M e n u ( l m e n u , _ ( " L a n g u a g e " ) ) ; 
 # i f   w x U S E _ R I C H T E X T 
 	 m e n u - > A p p e n d ( I D _ S Y M B O L , _ ( " S y m b o l " ) ) ; 
 # e n d i f / / w x U S E _ R I C H T E X T  
 	 m e n u - > A p p e n d C h e c k I t e m ( I D _ N O T I F Y , _ ( " N o t i f y " ) ) ; 
 	 m e n u - > A p p e n d C h e c k I t e m ( I D _ A U T O S T A R T , _ ( " A u t o s t a r t " ) ) ;  
 	 m e n u - > A p p e n d S e p a r a t o r ( ) ;  
 	 m e n u - > A p p e n d C h e c k I t e m ( I D _ I M P O R T , _ ( " I m p o r t " ) ) ;  
 	 m e n u - > A p p e n d C h e c k I t e m ( I D _ E X P O R T , _ ( " E x p o r t " ) ) ; 
 	 m e n u - > A p p e n d S e p a r a t o r ( ) ; 
 	 m e n u - > A p p e n d ( w x I D _ E X I T , _ ( " E x i t " ) ) ; 
 	 / / r e a d   v a l u e   f r o m   c o n f i g 
 	 b o o l   t e s t _ b o o l =   f a l s e ; 
 	 w x C o n f i g : : G e t ( ) - > R e a d ( _ T ( " / y e a r s e l e c t o r " ) , & t e s t _ b o o l , f a l s e ) ; 
 	 m e n u - > C h e c k ( I D _ Y E A R S E L , t e s t _ b o o l ) ; 
 	 w x C o n f i g : : G e t ( ) - > R e a d ( _ T ( " / a u t o s t a r t " ) , & t e s t _ b o o l , t r u e ) ; 
 	 m e n u - > C h e c k ( I D _ A U T O S T A R T , t e s t _ b o o l ) ; 
 	 / / w x C o n f i g : : G e t ( ) - > R e a d ( _ T ( " / n o t i f y " ) , & t e s t _ b o o l , f a l s e ) ; 
 	 / / m e n u - > C h e c k ( I D _ N O T I F Y , t e s t _ b o o l ) ; 
 
 	 r e t u r n   m e n u ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u E x i t ( w x C o m m a n d E v e n t &   W X U N U S E D ( e v e n t ) ) 
 { 
 	 f r a m e - > D e s t r o y ( ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u H i d e ( w x C o m m a n d E v e n t &   W X U N U S E D ( e v e n t ) ) 
 { 
 	 f r a m e - > H i d e ( ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u S h o w ( w x C o m m a n d E v e n t &   W X U N U S E D ( e v e n t ) ) 
 { 
 	 f r a m e - > S h o w ( ) ; 
 	 f r a m e - > S e t F o c u s ( ) ; 
 	 f r a m e - > R a i s e ( ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u O p c ( w x C o m m a n d E v e n t &   e v e n t ) 
 { 
 	 o p c   =   e v e n t . G e t I d ( ) ; 
 	 s w i t c h   ( o p c ) 
 	 { 
 	 	 c a s e   I D _ O P C 2 5 : 
 	 	 	 a l p h a   =   6 2 ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ O P C 5 0 : 
 	 	 	 a l p h a   =   1 2 5 ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ O P C 7 5 : 
 	 	 	 a l p h a   =   1 8 7 ; 
 	 	 	 b r e a k ; 
 	 	 d e f a u l t : 
 	 	 	 a l p h a   =   2 5 5 ; 
 	 	 	 b r e a k ; 
 	 } 
 	 f r a m e - > S e t T r a n s p a r e n t ( a l p h a ) ; 
 	 w x C o n f i g : : G e t ( ) - > W r i t e ( _ T ( " / o p a c i t y " ) , a l p h a ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u N o t e s C o l o u r ( w x C o m m a n d E v e n t &   e v e n t ) 
 { 
 	 w x C o l o u r D i a l o g   d l g ( f r a m e ) ; 
 	 d l g . G e t C o l o u r D a t a ( ) . S e t C h o o s e F u l l ( t r u e ) ; 
 	 i f   ( d l g . S h o w M o d a l ( )   = =   w x I D _ O K ) 
 	 { 
 	 	 e v e n t . S e t S t r i n g ( d l g . G e t C o l o u r D a t a ( ) . G e t C o l o u r ( ) . G e t A s S t r i n g ( w x C 2 S _ H T M L _ S Y N T A X ) ) ; 
 	 	 : : w x P o s t E v e n t ( f r a m e - > G e t E v e n t H a n d l e r ( ) , e v e n t ) ; 
 	 } 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u F i n d ( w x C o m m a n d E v e n t &   e v e n t ) 
 { 
 	 w x P o s t E v e n t ( f r a m e - > G e t E v e n t H a n d l e r ( ) , e v e n t ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n Y e a r S e l ( w x C o m m a n d E v e n t &   e v e n t ) 
 { 
 	 w x C o n f i g : : G e t ( ) - > W r i t e ( _ T ( " / y e a r s e l e c t o r " ) , e v e n t . I s C h e c k e d ( ) ) ; 
 	 w x P o s t E v e n t ( f r a m e - > G e t E v e n t H a n d l e r ( ) , e v e n t ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u A u t o S t a r t ( w x C o m m a n d E v e n t &   e v e n t ) 
 { 
 	 w x C o n f i g : : G e t ( ) - > W r i t e ( _ T ( " / a u t o s t a r t " ) , e v e n t . I s C h e c k e d ( ) ) ; 
 	 a s t a r t . S e t ( e v e n t . I s C h e c k e d ( ) ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u S y m b o l s ( w x C o m m a n d E v e n t &   W X U N U S E D ( e v e n t ) ) 
 { 
 # i f   w x U S E _ R I C H T E X T 
 	 w x S y m b o l P i c k e r D i a l o g   d l g ( _ T ( " * " ) , w x E m p t y S t r i n g , 
 	 	 	 	 	 	 	   w x T h e A p p - > G e t T o p W i n d o w ( ) - > G e t F o n t ( ) . G e t F a c e N a m e ( ) , N U L L ) ; 
 	 i f   ( d l g . S h o w M o d a l ( )   = = w x I D _ O K   & &   d l g . H a s S e l e c t i o n ( ) ) 
 	 { 
 	 	 i f   ( w x T h e C l i p b o a r d - > O p e n ( ) ) 
 	 	 { 
 	 	 	 w x T h e C l i p b o a r d - > S e t D a t a ( n e w   w x T e x t D a t a O b j e c t ( d l g . G e t S y m b o l ( ) ) ) ; 
 	 	 	 w x T h e C l i p b o a r d - > C l o s e ( ) ; 
 	 	 } 
 	 } 
 # e n d i f / / w x U S E _ R I C H T E X T 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u N o t i f y ( w x C o m m a n d E v e n t &   e v e n t ) 
 { 
 	 i f   ( e v e n t . I s C h e c k e d ( ) ) 
 	 { 
 	 	 w x N u m b e r E n t r y D i a l o g   d l g ( w x T h e A p p - > G e t T o p W i n d o w ( ) , _ ( " D a y s   t o   n o t i f y   b e f o r e   n o t e " ) , _ ( " D a y s " ) , 
 	 	 	 	 _ ( " N o t i f y " ) , 1 , 0 , 3 6 5 ) ; 
 	 	 i f   ( d l g . S h o w M o d a l ( )   = =   w x I D _ O K ) 
 	 	 { 
 	 	 	 w x C o n f i g : : G e t ( ) - > W r i t e ( _ T ( " / n o t i f y " ) , t r u e ) ; 
 	 	 } 
 	 } 
 	 e l s e 
 	 	 w x C o n f i g : : G e t ( ) - > W r i t e ( _ T ( " / n o t i f y " ) , f a l s e ) ; 
 } 
 
 v o i d   A g e n d e r T r a y : : O n M e n u L a n g ( w x C o m m a n d E v e n t &   e v e n t ) 
 { 
 	 w x L a n g u a g e   l   =   w x L A N G U A G E _ U N K N O W N ; 
 	 s w i t c h   ( e v e n t . G e t I d ( ) ) 
 	 { 
 	 	 c a s e   I D _ L A N G _ D E F : 
 	 	 	 l   =   w x L A N G U A G E _ D E F A U L T ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ E S : 
 	 	 	 l   =   w x L A N G U A G E _ S P A N I S H ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ D E : 
 	 	 	 l   =   w x L A N G U A G E _ G E R M A N ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ J A : 
 	 	 	 l   =   w x L A N G U A G E _ J A P A N E S E ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ S V : 
 	 	 	 l   =   w x L A N G U A G E _ S W E D I S H ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ F R : 
 	 	 	 l   =   w x L A N G U A G E _ F R E N C H ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ P T : 
 	 	 	 l   =   w x L A N G U A G E _ P O R T U G U E S E ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ E L : 
 	 	 	 l   =   w x L A N G U A G E _ G R E E K ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ Z H _ H K : 
 	 	 	 l   =   w x L A N G U A G E _ C H I N E S E _ H O N G K O N G ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ Z H _ C N : 
 	 	 	 l   =   w x L A N G U A G E _ C H I N E S E _ S I M P L I F I E D ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ H E : 
 	 	 	 l   =   w x L A N G U A G E _ H E B R E W ; 
 	 	 	 b r e a k ; 
 	 	 c a s e   I D _ L A N G _ R O : 
 	 	 	 l   =   w x L A N G U A G E _ R O M A N I A N ; 
 	 	 	 b r e a k ; 
 	 	 d e f a u l t : 
 	 	 	 l   =   w x L A N G U A G E _ D E F A U L T ; 
 	 	 	 b r e a k ; 
 	 } 
 	 w x C o n f i g : : G e t ( ) - > W r i t e ( _ T ( " / l a n g " ) , ( l o n g ) l ) ; 
 	 w x M e s s a g e B o x ( _ T ( " T o   a p p l y   c h a n g e s   y o u   m u s t   r e s t a r t   A g e n d e r " ) , 
 	 	 _ ( " A g e n d e r   L a n g u a g e   c h a n g e d " ) , w x O K , f r a m e ) ; 
 }  
  
 v o i d   A g e n d e r T r a y : : O n M e n u I m p o r t ( w x C o m m a n d E v e n t &   e v e n t )  
 {  
 	 w x F i l e D i a l o g   d l g ( 0 ) ;  
 	 d l g . S e t W i l d c a r d ( _ T ( " A g e n d e r   f i l e s | * . x m l ; * . t x t " ) ) ;  
 	 i f   ( d l g . S h o w M o d a l ( )   = =   w x I D _ O K )  
 	 {  
 	 	 A g C a l : : G e t ( ) - > I m p o r t ( d l g . G e t F i l e n a m e ( ) ) ;  
 	 }  
 }  
  
 v o i d   A g e n d e r T r a y : : O n M e n u E x p o r t ( w x C o m m a n d E v e n t &   e v e n t )  
 {  
 	 w x F i l e D i a l o g   d l g ( 0 ) ;  
 	 d l g . S e t W i l d c a r d ( _ T ( " A g e n d e r   x m l | * . x m l " ) ) ;  
 	 i f   ( d l g . S h o w M o d a l ( )   = =   w x I D _ O K )  
 	 {  
 	 	 A g C a l : : G e t ( ) - > E x p o r t ( d l g . G e t P a t h ( ) ) ;  
 	 }  
 } 
 
 # e n d i f   / / w x H A S _ T A S K _ B A R _ I C O N 
 